//
// Created by 张程易 on 31/10/2017.
//

#include "FuckScript.h"
#include "StandardAssets.h"


void FuckScript::start() {
    text = getGameObject()->getComponent<Text>();
    cb = std::bind(&FuckScript::onClick, this);
    Input::attachOnMouseClick(0, Utility::SCREEN_WIDTH, 0, Utility::SCREEN_WIDTH, 0, &cb, nullptr);

}

void FuckScript::update() {
    if (cnt != 0) {
        cnt--;
        if (cnt == 0) {
            text->setText("");
        }
        return;
    }
}

FuckScript::FuckScript(GameObject *human) : human(human) {}

void FuckScript::onClick() {
    AABBCollider *collider = AABBCollider::raycast(
            Runtime::getCamera()->getGameObject()->transform.getPosition(),
            Runtime::getCamera()->getGameObject()->transform.getForward(),
            100000.0f
    );
    if (collider == nullptr) {
        text->setText("NO");
    } else {
        text->setText("YES");
    }
    cnt = 5;
}



