//
// Created by 张程易 on 30/10/2017.
//

#include "DefaultCamera.h"

void DefaultCamera::processKeyboard(Camera::Direction direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction == Direction::FORWARD)
        transform.translate(front * velocity);
    if (direction == Direction::BACKWARD)
        transform.translate(front * velocity);
    if (direction == Direction::LEFT)
        transform.translate(right * velocity);
    if (direction == Direction::RIGHT)
        transform.translate(right * velocity);
}

void DefaultCamera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Eular angles
    updateCameraVectors();
}

void DefaultCamera::processMouseScroll(float yoffset) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void DefaultCamera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = (float)( cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    front.y = (float)( sin(glm::radians(pitch)));
    front.z = (float)( sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, front));
}

glm::mat4 DefaultCamera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

DefaultCamera::DefaultCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float zoom, float sensitivity,
                             float speed) :
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed(speed),
        mouseSensitivity(sensitivity),
        zoom(zoom),
        position(position),
        worldUp(up),
        yaw(yaw),
        pitch(pitch) {
    updateCameraVectors();
}

glm::mat4 DefaultCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(zoom), (float)Utility::SCREEN_WIDTH / (float)Utility::SCREEN_HEIGHT, 0.1f, 100.0f);
}
