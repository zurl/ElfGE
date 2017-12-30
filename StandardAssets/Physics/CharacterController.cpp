//
// Created by 张程易 on 27/12/2017.
//

#include "CharacterController.h"

void CharacterController::start() {
    enableMouseInput();
    rigidBody = getGameObject()->getComponent<RigidBody>();
}

void CharacterController::update() {
    if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS){
        rigidBody->translate(speed * getGameObject()->transform.getLocalForward());
    }
    if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS){
        rigidBody->translate(-speed * getGameObject()->transform.getLocalForward());
    }
    if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS){
        rigidBody->translate(-speed * getGameObject()->transform.getLocalRight());
    }
    if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
        rigidBody->translate(speed * getGameObject()->transform.getLocalRight());
    }
}

void CharacterController::onMouseMove(double xpos, double ypos) {

    static double lastX= Utility::SCREEN_WIDTH / 2;

    double xoffset =  xpos - lastX;

    lastX = xpos;

    xoffset *= mouseSensitivity ;

    getGameObject()->transform.rotate(Transform::up, -xoffset);
}

CharacterController::CharacterController(float mouseSensitivity, float speed) : mouseSensitivity(mouseSensitivity),
                                                                                speed(speed) {}
