//
// Created by 张程易 on 26/12/2017.
//

#include "RigidBody.h"

void RigidBody::onCollisionEnter(Collider *collider, glm::vec3 info) {
    printf(("in" + collider->getGameObject()->getName() + "\n").c_str());
    AABBCollider * aabb = (AABBCollider * )collider;
    if(!aabb->isWall())return;
    this->collider = aabb;
    this->info = info;
    GameScript::onCollisionEnter(collider, info);
}

void RigidBody::onCollisionExit(Collider *collider) {
    this->collider = nullptr;
    GameScript::onCollisionExit(collider);
}

void RigidBody::translate(glm::vec3 x) {
    if(collider != nullptr){
        if(x.x * info.x < 0) x.x = 0;
        if(x.y * info.y < 0) x.y = 0;
        if(x.z * info.z < 0) x.z = 0;
        getGameObject()->transform.translate(x);
    }
    else{
        getGameObject()->transform.translate(x);
    }
}
