//
// Created by 张程易 on 31/10/2017.
//

#include "FuckScript.h"
#include "StandardAssets.h"


void FuckScript::start() {
    text = getGameObject()->getComponent<Text>();
}

void FuckScript::update() {
    if (cnt != 0) {
        cnt--;
        if (cnt == 0) {
            text->setText("");
        }
        return;
    }
    cb = std::bind(&FuckScript::onClick, this);
    Input::attachOnMouseClick(0, Utility::SCREEN_WIDTH, 0, Utility::SCREEN_WIDTH, 0, &cb, nullptr);
}

FuckScript::FuckScript(GameObject *human) : human(human) {}

void FuckScript::onClick() {
    AABBCollider *collider = AABBCollider::raycast(
            Runtime::getCamera()->getGameObject()->transform.getPosition(),
            Runtime::getCamera()->getGameObject()->transform.getForward(),
            100000.0f
    );

    //auto cube = set<Cube>(glm::vec3(0.0f, 1.0f, 0.0))->createComponent<EnemyCond>(5,1, human);
    human->getComponent<AnimationCond>()->play(3);
    if (collider == nullptr) {
        text->setText("NO");
    } else {
        text->setText("YES");

        EnemyCond * thisEnmey = collider->getGameObject()->getComponent<EnemyCond>();

        if(thisEnmey->Health-- <= 0){
            thisEnmey->die();
        }


    }
    cnt = 5;
}



