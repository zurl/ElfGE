//
// Created by 张程易 on 23/12/2017.
//

#include "DeveloperScript.h"

void DeveloperScript::start() {
    enter = std::bind(&DeveloperScript::onClickEnter, this);
    Input::attachOnMouseClick(-10, 0, 0, 0, 0, &enter, nullptr);

    // create UI

    UIRoot = new GameObject("DeveloperUIRoot");
    UIRoot->createComponent<Text>();


    auto text1go = new GameObject("text1")
            ->createComponent<Text>(text, font);

    text2->setParent(canvas);
    text2->transform.translate(pos);
    text2->transform.setScale(glm::vec3(size));
    return text2;

    auto = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 20, 0), 0.5);
    auto dt2 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 60, 0), 0.5);
    auto dt3 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 100, 0), 0.5);

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
            if(target != nullptr) {
                auto rnd = target->getComponent<Renderer>();
                if (rnd != nullptr) {
                    rnd->setSelected(false);
                }
            }
            controller->setParent(nullptr);
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
            Runtime::getCamera()->getGameObject()->getWorldPosition(),
            Runtime::getCamera()->getGameObject()->getWorldForward(),
            100000.0f
    );
    if(target != nullptr){
        auto rnd = target->getComponent<Renderer>();
        if( rnd != nullptr ){
            rnd->setSelected(false);
        }
        target = nullptr;
    }
    if (collider == nullptr) {
        status = "Selected: None";
        components = "";
        updateText();
    } else {
        target = collider->getGameObject();
        status = "Selected: ";
        auto rnd = target->getComponent<Renderer>();
        if( rnd != nullptr ){
            rnd->setSelected(true);
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
        auto pos = target->getWorldPosition();
        auto rot = target->getWorldRotation();
        auto sca = target->getWorldScale();
        sprintf(buf, "P(%0.2f, %0.2f, %0.2f) R(%0.2f, %0.2f, %0.2f) S(%0.2f, %0.2f, %0.2f)",
                pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, sca.x, sca.y, sca.z
        );
        text3->setText(buf);
    }
    else{
        text3->setText("");
    }
    text1->setText(status + components);
}

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
    else if(setType == 2) target->transform.setScale(target->transform.getLocalScale() + delta);
    else {
        if(setAxis == 0)target->transform.rotate(Transform::up, d);
        else if(setAxis == 1)target->transform.rotate(Transform::forward, d);
        else if(setAxis == 2)target->transform.rotate(Transform::right, d);
    }
}

DeveloperScript::DeveloperScript(){}

GameObject *DeveloperScript::getUIRoot() const {
    return UIRoot;
}
