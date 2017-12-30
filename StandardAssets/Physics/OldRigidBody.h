//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_RIGIDBODY_H
#define ELFGE_RIGIDBODY_H

#include "GameEngine.h"

const float g = 9.78f;

class OldRigidBody : public GameScript {
    bool onCollision;
public:
    float mass;
    float collisionK;
    bool isTrigger, useGravity, isFace = false;
    glm::vec3 velocity, force;

    std::string getName() override;

    OldRigidBody(float mass,
              const glm::vec3 &velocity = glm::vec3(0, 0, 0),
              const glm::vec3 &force = glm::vec3(0, 0, 0),
              float collisionK = 0,
              bool isTrigger = true,
              bool useGravity = false);

    void start() override;

    void update() override;

    void onCollisionEnter(Collider *collider, glm::vec3 info) override;

    void onCollisionExit(Collider *collider) override;

};


#endif //ELFGE_RIGIDBODY_H
