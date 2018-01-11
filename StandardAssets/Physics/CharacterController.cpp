//
// Created by 张程易 on 27/12/2017.
//

#include "CharacterController.h"
#include "../../Assets/LJK/AnimationCond.h"

void CharacterController::start() {
    enableMouseInput();
    rigidBody = getGameObject()->getComponent<RigidBody>();
}

void CharacterController::update() {
//    if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS){
//        rigidBody->translate(speed * getGameObject()->transform.getLocalForward());
//    }
//    if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS){
//        rigidBody->translate(-speed * getGameObject()->transform.getLocalForward());
//    }
//    if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS){
//        rigidBody->translate(-speed * getGameObject()->transform.getLocalRight());
//    }
//    if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
//        rigidBody->translate(speed * getGameObject()->transform.getLocalRight());
//    }
        if(glfwGetKey(Utility::window, GLFW_KEY_C) == GLFW_PRESS){
            if(glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){

                Human->getComponent<AnimationCond>()->play(5);
                if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS){
                    rigidBody->translate(speed * getGameObject()->transform.getLocalForward());
                    //humanrg->translate(humanspeed * human->transform.getLocalRight());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS){
                    rigidBody->translate(-speed * getGameObject()->transform.getLocalForward());
                    //humanrg->translate(-humanspeed * human->transform.getLocalRight());
                }

                if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS){
                    rigidBody->translate(-speed * getGameObject()->transform.getLocalRight());
                    //humanrg->translate(humanspeed * human->transform.getLocalForward());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
                    rigidBody->translate(speed * getGameObject()->transform.getLocalRight());
                    //humanrg->translate(-humanspeed * human->transform.getLocalForward());
                }
            }
            else{
                Human->getComponent<AnimationCond>()->play(4);
            }

        }
        else{
            if(glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
                Human->getComponent<AnimationCond>()->play(1);
                if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS){
                    rigidBody->translate(speed * getGameObject()->transform.getLocalForward());
                    //humanrg->translate(humanspeed * human->transform.getLocalRight());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS){
                    rigidBody->translate(-speed * getGameObject()->transform.getLocalForward());
                    //humanrg->translate(-humanspeed * human->transform.getLocalRight());
                }

                if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS){
                    rigidBody->translate(-speed * getGameObject()->transform.getLocalRight());
                    //humanrg->translate(humanspeed * human->transform.getLocalForward());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
                    rigidBody->translate(speed * getGameObject()->transform.getLocalRight());
                    //humanrg->translate(-humanspeed * human->transform.getLocalForward());
                }
            }
            else if(glfwGetKey(Utility::window, GLFW_KEY_SPACE) == GLFW_PRESS){
                Human->getComponent<AnimationCond>()->play(2);
            }
            else{
                Human->getComponent<AnimationCond>()->play(0);
            }

        }

}

void CharacterController::onMouseMove(double xpos, double ypos) {

    static double lastX= Utility::SCREEN_WIDTH / 2;

    double xoffset =  xpos - lastX;

    lastX = xpos;

    xoffset *= mouseSensitivity ;

    getGameObject()->transform.rotate(Transform::up, -xoffset);
}

CharacterController::CharacterController(GameObject * human, float mouseSensitivity, float speed) : Human(human), mouseSensitivity(mouseSensitivity),speed(speed) {}
