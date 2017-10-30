//
// Created by 张程易 on 30/10/2017.
//

#include "DefaultCamera.h"

//void DefaultCamera::processKeyboard(Direction direction, float deltaTime) {
//    float velocity = movementSpeed * deltaTime;
//    if (direction == Direction::FORWARD)
//        getParent()->transform.translate(front * velocity);
//    if (direction == Direction::BACKWARD)
//        getParent()->transform.translate(front * velocity);
//    if (direction == Direction::LEFT)
//        getParent()->transform.translate(right * velocity);
//    if (direction == Direction::RIGHT)
//        getParent()->transform.translate(right * velocity);
//}


glm::mat4 DefaultCamera::getViewMatrix() {
    return glm::lookAt(getParent()->transform.getPosition(),
                       getParent()->transform.getPosition() + front,
                       getParent()->transform.getQuatMatrix() * Transform::up);
}

glm::mat4 DefaultCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(zoom), (float)Utility::SCREEN_WIDTH / (float)Utility::SCREEN_HEIGHT, 0.1f, 100.0f);
}


DefaultCamera::DefaultCamera(glm::vec3 position, glm::vec3 rotation,glm::vec3 front, float zoom, float sensitivity,
                             float speed) :
        movementSpeed(speed),
        mouseSensitivity(sensitivity),
        zoom(zoom),
        front(front)
{}

