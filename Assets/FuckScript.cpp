//
// Created by 张程易 on 31/10/2017.
//

#include "FuckScript.h"
#include "Prefabs.h"



void FuckScript::start() {

}

void FuckScript::update() {
    if( cnt != 0){
        cnt --;
        return;
    }
    if( glfwGetKey(Utility::window, GLFW_KEY_Q) == GLFW_PRESS){
        cnt = 50;
        auto a = instantiate<Prefabs::Cube>(getGameObject()->transform.getPosition());
        a->transform.setScale(glm::vec3(0.2));
        auto r = a->getComponent<RigidBody>();
        r->velocity = (getGameObject()->transform.getForward() * 0.15f);
    }
}
