//
// Created by 张程易 on 26/12/2017.
//

#ifndef ELFGE_RIGIDBODY_H
#define ELFGE_RIGIDBODY_H

#include <Physics/Colliders/AABBCollider.h>
#include "GameEngine.h"

class RigidBody: public GameScript {
    AABBCollider * collider = nullptr;
    glm::vec3 info;
public:
    void onCollisionEnter(Collider *collider, glm::vec3 info) override;

    void onCollisionExit(Collider *collider) override;

    void translate(glm::vec3 x);
};


#endif //ELFGE_RIGIDBODY_H
