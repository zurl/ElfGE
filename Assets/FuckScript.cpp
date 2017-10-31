//
// Created by 张程易 on 31/10/2017.
//

#include "FuckScript.h"

void FuckScript::start() {

}

void FuckScript::update() {

}

void FuckScript::onCollisionEnter(Collider *collider) {
    printf("Enter !!!\n");
    GameScript::onCollisionEnter(collider);
}

void FuckScript::onCollisionExit(Collider *collider) {
    printf("Exit !!!\n");
    GameScript::onCollisionExit(collider);
}
