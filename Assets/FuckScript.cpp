//
// Created by 张程易 on 31/10/2017.
//

#include "FuckScript.h"
#include "Prefabs.h"



void FuckScript::start() {
    text = getGameObject()->getComponent<Text>();
}

void FuckScript::update() {
    if( cnt != 0){
        cnt --;
        return;
    }
    if( glfwGetMouseButton(Utility::window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS){
        AABBCollider * collider = AABBCollider::raycast(
                Runtime::getCamera()->getGameObject()->transform.getPosition(),
                Runtime::getCamera()->getGameObject()->transform.getForward(),
                100000.0f
        );
        if( collider == nullptr){
            text->setText("NO");
        }
        else{
            text->setText("YES");
            //collider->getGameObject()->transform.translate(Transform::up);
        }
        cnt = 0;
    }
}

FuckScript::FuckScript(GameObject *human) : human(human) {}
