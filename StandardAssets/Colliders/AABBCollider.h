//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_AABBCOLLIDER_H
#define ELFGE_AABBCOLLIDER_H

#include "../../GameEngine/GameEngine.h"

class AABBCollider: public Collider {

    static std::list<AABBCollider *> allColliders;

    bool autogen = false;
    bool passive;

    std::set<AABBCollider *> onCollision;

    glm::vec3 offset;
    glm::vec3 size;
    std::vector<glm::vec3> vertices;
    glm::vec3 min, max;

    void computerBox();

    bool checkAxis(float minA, float maxA, float minB, float maxB);

    bool checkCollision(AABBCollider * dst);

public:

    AABBCollider(const glm::vec3 &size,
                 const glm::vec3 &offset = glm::vec3(0, 0, 0),
                 bool passive = true
                 );

    AABBCollider(bool passive = true);

    void start() override;

    void update() override;

    void destroy() override;

};


#endif //ELFGE_AABBCOLLIDER_H
