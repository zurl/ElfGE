//
// Created by 张程易 on 31/10/2017.
//

#include "ShootScript.h"
#include "StandardAssets.h"
#include "../LJK/EnemyCond.h"


void ShootScript::start() {
    //text = getGameObject()->getComponent<Text>();
    cb = std::bind(&ShootScript::onClick, this);
    Input::attachOnMouseClick(-10, Utility::SCREEN_WIDTH, 0, Utility::SCREEN_WIDTH, 0, &cb, nullptr);
}

ShootScript::ShootScript(GameObject *human) : human(human) {}

void ShootScript::onClick() {
    AABBCollider *collider = AABBCollider::raycast(
            Runtime::getCamera()->getGameObject()->getWorldPosition(),
            Runtime::getCamera()->getGameObject()->getWorldForward(),
            100000.0f,
            human->getComponent<AABBCollider>()
    );

    if (collider){
        printf("ok\n");
        auto thisEnemy = collider->getGameObject()->getComponent<EnemyCond>();
        if(thisEnemy){
            thisEnemy->Health--;
            thisEnemy->getGameObject()->getComponent<AnimationCond>()->play(7);
        }

    }

}

void ShootScript::sleep() {
    Input::detachOnMouseClick(&cb);

}

void ShootScript::awake() {
    Input::attachOnMouseClick(-10, Utility::SCREEN_WIDTH, 0, Utility::SCREEN_WIDTH, 0, &cb, nullptr);
}



