//
// Created by 张程易 on 31/10/2017.
//

#include "RigidBody.h"

void RigidBody::onCollisionEnter(Collider *collider) {
    if (!isTrigger && !isFace) {
        auto target = collider->getGameObject();
        auto rb = target->getComponent<RigidBody>();
        if (rb == nullptr) return;
        glm::vec3 directVector;
        if (rb->isFace) directVector = getGameObject()->transform.forward;
        else directVector = glm::normalize(target->transform.getPosition() - getGameObject()->transform.getPosition());

        float va = glm::dot(directVector, velocity);
        float vb = glm::dot(directVector, rb->velocity);
        float ma = mass;
        float mb = rb->mass;
        if (fabs(va) < 1e-4 && fabs(vb) < 1e-4) return;
        if ((va >= 0 && vb <= 0)
            || (va >= 0 && vb >= 0 && va >= vb)
            || (va <= 0 && vb <= 0 && va >= vb)) {

            printf("pz\n");
            float p = ma * va + mb * vb;
            float m = ma + mb;
            float vc = (collisionK * mb * (vb - va) + p) / m;
            float vd = (collisionK * ma * (va - vb) + p) / m;

            velocity += (vc - va) * directVector;
            rb->velocity += (vd - vb) * directVector;
            onCollision = true;

        }
    }
    GameScript::onCollisionEnter(collider);
}

void RigidBody::update() {
    velocity += (float) Utility::deltaTime / mass * force;
    if (useGravity) velocity += (float) Utility::deltaTime * g;
    getGameObject()->transform.translate(velocity);
}

void RigidBody::onCollisionExit(Collider *collider) {
    if (!isTrigger) {
        onCollision = false;

    }
    GameScript::onCollisionExit(collider);
}

void RigidBody::start() {

}

RigidBody::RigidBody(float mass, const glm::vec3 &velocity, const glm::vec3 &force, float collisionK, bool isTrigger,
                     bool useGravity) : mass(mass), collisionK(collisionK), isTrigger(isTrigger),
                                        useGravity(useGravity), velocity(velocity), force(force) {}

