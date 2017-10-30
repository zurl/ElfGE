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
    //auto ret = glm::rotate(getParent()->transform.getQuaternion(), Transform::forward);
    //std::cout<<"ro="<<ret.x<<" "<<ret.y<<" "<<ret.z<<std::endl;

    return glm::lookAt(getParent()->transform.getPosition(),
                       getParent()->transform.getPosition()
                       + glm::rotate(getParent()->transform.getQuaternion(), Transform::forward),
                       Transform::up);
    //glm::rotate(getParent()->transform.getQuaternion(), Transform::up));
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

void DefaultCamera::start() {
    enableMouseInput();
    enableScrollInput();
}

void DefaultCamera::update() {
    float cameraSpeed = (float)(2.5f * Utility::deltaTime);
    if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS)
        getParent()->transform.translate(cameraSpeed * getParent()->transform.getForward());
    if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS)
        getParent()->transform.translate(-cameraSpeed * getParent()->transform.getForward());
    if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS)
        getParent()->transform.translate(-cameraSpeed * getParent()->transform.getRight());
    if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS)
        getParent()->transform.translate(cameraSpeed * getParent()->transform.getRight());
}

void DefaultCamera::onMouseMove(double xpos, double ypos) {

    static double lastX = Utility::SCREEN_HEIGHT / 2, lastY = Utility::SCREEN_WIDTH / 2;

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    glm::vec3 rotation = getParent()->transform.getRotation();

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    rotation.y -= xoffset;
    rotation.z += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
//    if (constrainPitch) {
//        if (rotation.z > 89.0f)
//            rotation.z = 89.0f;
//        if (rotation.z < -89.0f)
//            rotation.z = -89.0f;
//    }
    //std::cout<<"roa="<<rotation.x<<" "<<rotation.y<<" "<<rotation.z<<std::endl;

    getParent()->transform.setRotation(rotation);
}

void DefaultCamera::onScrollMove(double x) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= x;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
    //std::cout<<"so="<<zoom<<std::endl;

}

