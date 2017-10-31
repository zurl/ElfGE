//
// Created by 张程易 on 31/10/2017.
//

#include "DefaultCamera.h"


glm::mat4 DefaultCamera::getViewMatrix() {
    return glm::lookAt(getGameObject()->transform.getPosition(),
                       getGameObject()->transform.getPosition()
                       + glm::rotate(getGameObject()->transform.getQuaternion(), Transform::forward),
                       Transform::up);
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