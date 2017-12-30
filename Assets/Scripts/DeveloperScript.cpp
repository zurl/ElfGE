//
// Created by 张程易 on 23/12/2017.
//

#include "DeveloperScript.h"

void DeveloperScript::start() {
    enter = std::bind(&DeveloperScript::onClickEnter, this);
    Input::attachOnMouseClick(-10, 0, 0, 0, 0, &enter, nullptr);
}

void DeveloperScript::update() {
    if(keyCounter != 0){
        keyCounter --;
        return;
    }
    if (glfwGetKey(Utility::window, GLFW_KEY_L) == GLFW_PRESS){
        if(enable){
            enable = false;
            status = "Developer Mode: OFF";
            components = "";
            auto rnd = target->getComponent<Renderer>();
            if( rnd != nullptr ){
                rnd->setMaterial(savedMaterial);
            }
            target = nullptr;
        }
        else{
            enable = true;
            status = "Developer Mode: ON";
        }
        text2->setText("");
        updateText();
        keyCounter = 100;
    }
    if(target != nullptr){
        if (glfwGetKey(Utility::window, GLFW_KEY_1) == GLFW_PRESS){
            setType = 0; updateState(); keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_2) == GLFW_PRESS){
            setType = 1; updateState(); keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_3) == GLFW_PRESS){
            setType = 2; updateState(); keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_4) == GLFW_PRESS){
            setAxis = 0; updateState(); keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_5) == GLFW_PRESS){
            setAxis = 1; updateState(); keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_6) == GLFW_PRESS){
            setAxis = 2; updateState(); keyCounter = 5;
        }
        if (target && glfwGetKey(Utility::window, GLFW_KEY_7) == GLFW_PRESS){
            adjust(len); updateText(); keyCounter = 5;
        }
        if (target && glfwGetKey(Utility::window, GLFW_KEY_8) == GLFW_PRESS){
            adjust(-len); updateText(); keyCounter = 5;
        }
        if (target && glfwGetKey(Utility::window, GLFW_KEY_9) == GLFW_PRESS){
            len += 0.1; updateState(); keyCounter = 5;
        }
        if (target && glfwGetKey(Utility::window, GLFW_KEY_0) == GLFW_PRESS){
            len -= 0.1; updateState(); keyCounter = 5;
        }
    }
}

void DeveloperScript::onClickEnter() {
    if(!enable) return;
    AABBCollider *collider = AABBCollider::raycast(
            Runtime::getCamera()->getGameObject()->transform.getPosition(),
            Runtime::getCamera()->getGameObject()->transform.getForward(),
            100000.0f
    );
    if (collider == nullptr) {
        status = "Selected: None";
        components = "";
        if(target != nullptr){
            auto rnd = target->getComponent<Renderer>();
            if( rnd != nullptr ){
                rnd->setMaterial(savedMaterial);
            }
            target = nullptr;
        }
        updateText();
    } else {
        if(target != nullptr){
            auto rnd = target->getComponent<Renderer>();
            if( rnd != nullptr ){
                rnd->setMaterial(savedMaterial);
            }
            target = nullptr;
        }
        target = collider->getGameObject();
        status = "Selected: ";
        auto rnd = target->getComponent<Renderer>();
        if( rnd != nullptr ){
            savedMaterial = rnd->getMaterial();
            rnd->setMaterial(selectMaterial);
        }
        if(target->getName() != "") status += target->getName();
        else status += " Nameless Object";
        components = "(";
        for(auto comp : target->getComponents()){
            components += "[" + comp->getName() + "]";
        }
        components += ")";
    }
    updateText();
    updateState();
}

void DeveloperScript::updateText() {
    char buf[512];
    if(target){
        auto pos = target->transform.getPosition();
        auto rot = target->transform.getRotation();
        auto sca = target->transform.getScale();
        sprintf(buf, "P(%0.2f, %0.2f, %0.2f) P(%0.2f, %0.2f, %0.2f) S(%0.2f, %0.2f, %0.2f)",
        pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, sca.x, sca.y, sca.z
        );
        text3->setText(buf);
    }
    else{
        text3->setText("");
    }
    text1->setText(status + components);
}

DeveloperScript::DeveloperScript(Text *text1, Text *text2, Text *text3) : text1(text1), text2(text2), text3(text3) {}

void DeveloperScript::updateState() {
    state = "";
    if(setType == 0) state += "Position";
    else if(setType == 1) state += "Rotation";
    else if(setType == 2) state += "Scale";
    state += ",";
    if(setAxis == 0) state += "Axis: X";
    else if(setAxis == 1) state += "Axis: Y";
    else if(setAxis == 2) state += "Axis: Z";
    state += ",Delta: " + std::to_string(len);
    text2->setText(state);
}

void DeveloperScript::adjust(float d) {
    glm::vec3 delta;
    if(setAxis == 0) delta.x = d;
    else if(setAxis == 1) delta.y = d;
    else if(setAxis == 2) delta.z = d;
    if(setType == 0) target->transform.translate(delta);
    else if(setType == 2) target->transform.setScale(target->transform.getScale() + delta);
    else {
        if(setAxis == 0)target->transform.rotate(Transform::up, d);
        else if(setAxis == 1)target->transform.rotate(Transform::forward, d);
        else if(setAxis == 2)target->transform.rotate(Transform::right, d);
    }
}
