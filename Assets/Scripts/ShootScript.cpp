//
// Created by 张程易 on 31/10/2017.
//

#include "FuckScript.h"
#include "StandardAssets.h"
#include "../LJK/EnemyCond.h"


void FuckScript::start() {
    //text = getGameObject()->getComponent<Text>();
    cb = std::bind(&FuckScript::onClick, this);
    Input::attachOnMouseClick(-10, Utility::SCREEN_WIDTH, 0, Utility::SCREEN_WIDTH, 0, &cb, nullptr);

}

void FuckScript::update() {

}

FuckScript::FuckScript(GameObject *human) : human(human) {}

void FuckScript::onClick() {
    AABBCollider *collider = AABBCollider::raycast(
            Runtime::getCamera()->getGameObject()->getWorldPosition(),
            Runtime::getCamera()->getGameObject()->getWorldForward(),
            100000.0f,
            human->getComponent<AABBCollider>()
    );
    if (collider == nullptr) {
        printf("111");

    } else {

        printf("%s##fucked!\n", collider->getGameObject()->getName().c_str());

        auto thisEnemy = collider->getGameObject()->getComponent<EnemyCond>();
        if(thisEnemy){
            thisEnemy->Health--;
            thisEnemy->getGameObject()->getComponent<AnimationCond>()->play(7);
        }


    }

}



