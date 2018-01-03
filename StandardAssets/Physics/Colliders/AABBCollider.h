//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_AABBCOLLIDER_H
#define ELFGE_AABBCOLLIDER_H

#include "GameEngine.h"

class AABBCollider : public Collider {

public:
    static std::list<AABBCollider *> allColliders;

    bool autogen = false;
    bool wall = true;
    bool passive;

    std::set<AABBCollider *> onCollision;

    glm::vec3 offset;
    glm::vec3 size;
    std::vector<glm::vec3> vertices;

    float radius;

    void computeBox();

    static bool checkAxis(float minA, float maxA, float minB, float maxB);

    int getAxisInfo(float minA, float maxA, float minB, float maxB);

    bool checkCollision(AABBCollider *dst);

    glm::vec3 getCollisionInfo(AABBCollider *dst);

public:

    std::string getName() override;

    AABBCollider(const glm::vec3 &size,
                 const glm::vec3 &offset = glm::vec3(0, 0, 0),
                 bool passive = true,
                 bool wall = true
    );

    AABBCollider(bool passive = true, bool wall = true);

    void start() override;

    void update() override;

    void destroy() override;

    bool testRaycast(glm::vec3 origin, glm::vec3 direction);

    static AABBCollider *raycast(
            glm::vec3 origin,
            glm::vec3 direction,
            float distance,
            AABBCollider * ignore = nullptr
    );

    const glm::vec3 &getOffset() const;

    const glm::vec3 &getSize() const;

    float getRadius() const;

    bool isWall() const;

    glm::vec3 min, max;
    glm::vec3 min0, max0;

    void setWall(bool w);
};


#endif //ELFGE_AABBCOLLIDER_H
