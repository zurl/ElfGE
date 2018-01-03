//
// Created by 张程易 on 31/10/2017.
//

#include "AABBCollider.h"
#include "../../Models/DefaultModel.h"

std::list<AABBCollider *> AABBCollider::allColliders;

void AABBCollider::start() {
    if (autogen) {
        autogen = false;
        min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
        max = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);
        auto model = getGameObject()->getComponent<DefaultModel>();
        if (model == nullptr) throw Exception("AutoGen Only Support Default Mesh");
        for (auto &mesh : model->meshes) {
            if (mesh == nullptr) throw Exception("AutoGen Only Support Default Mesh");
            for (auto &vertex : mesh->vertices) {
                min = glm::min(vertex.position, min);
                max = glm::max(vertex.position, max);
            }
        }
        offset = (min + max) * 0.5f;
        size = (max - min) * 0.5f;
        min0 = min;
        max0 = max;
    }
    computeBox();
    radius = std::max({
          std::abs(min.x),
          std::abs(min.y),
          std::abs(min.z),
          std::abs(max.x),
          std::abs(max.y),
          std::abs(max.z)
  }) * 2;
    allColliders.emplace_back(this);
}

void AABBCollider::update() {
    computeBox();
    if (!passive) {
        for (auto &x : allColliders) {
            if (x != this) {
                glm::vec3 pos = x->getGameObject()->getWorldPosition();
                float targetDis = glm::distance(getGameObject()->getWorldPosition(), pos);
                float dis = radius + x->radius;
                bool isOnCollision = onCollision.find(x) != onCollision.end();
                //if(!isOnCollision && targetDis > dis + 1e-1) continue;
                //printf("targetDis=%f, radius=%f\n", targetDis, dis);
                bool isCollision = checkCollision(x);
                if (isCollision && !isOnCollision) {
                    glm::vec3 info = getCollisionInfo(x);
                    onCollision.emplace(x);
                    auto result = this->getGameObject()->getComponents<GameScript>();
                    for (auto &y: result) {
                        y->onCollisionEnter(x, info);
                    }
                }
                if (!isCollision && isOnCollision) {
                    onCollision.erase(x);
                    auto result = this->getGameObject()->getComponents<GameScript>();
                    for (auto &y: result) {
                        y->onCollisionExit(x);
                    }
                }
            }
        }
    }
}

void AABBCollider::destroy() {
    allColliders.remove(this);
}

AABBCollider::AABBCollider(const glm::vec3 &size,
                           const glm::vec3 &offset,
                           bool passive,
                           bool wall
) : passive(passive), offset(offset), size(size), wall(wall) {
    min = offset - size;
    max = offset + size;
    min0 = min;
    max0 = max;

}

bool AABBCollider::checkCollision(AABBCollider *dst) {
   return checkAxis(this->min.x, this->max.x, dst->min.x, dst->max.x)
           && checkAxis(this->min.y, this->max.y, dst->min.y, dst->max.y)
           && checkAxis(this->min.z, this->max.z, dst->min.z, dst->max.z);
}

bool AABBCollider::checkAxis(float minA, float maxA, float minB, float maxB) {
    return !(maxA < minB || minA > maxB);
}

void AABBCollider::computeBox() {
    glm::vec3 scale = getGameObject()->getWorldScale();
    glm::vec3 pos = getGameObject()->getWorldPosition();
    min = min0 * scale + pos;
    max = max0 * scale + pos;
    //printf("%f %f %f %f %f %f\n", min.x, min.y, min.z, max.x, max.y, max.z);
}

AABBCollider::AABBCollider(bool passive, bool wall) : wall(wall) {
    autogen = true;
    this->passive = passive;
}

bool check2DRayCast(float ox, float oy, float dx, float dy,
                    float xl, float xr, float yl, float yr) {
    float k = dy / dx;
    float b = -k * ox + oy;
    float py1 = k * xl + b;
    float py2 = k * xr + b;
    float pyl = (float) fmin(py1, py2);
    float pyr = (float) fmax(py1, py2);
    return !(pyr < yl || pyl > yr);
}

AABBCollider *AABBCollider::raycast(glm::vec3 origin, glm::vec3 direction, float distance) {
    AABBCollider *result = nullptr;
    float resultDistance = FLT_MAX;
    for (auto target : allColliders) {
        glm::vec3 pos = target->getGameObject()->getWorldPosition();
        float targetDis = glm::distance(origin, pos);
        target->computeBox();
        if (targetDis < distance
            && target->testRaycast(origin, direction)
            && targetDis < resultDistance) {
            resultDistance = targetDis;
            result = target;
        }
    }
    return result;
}

std::string AABBCollider::getName() {
    return "AABBCollider";
}

const glm::vec3 &AABBCollider::getOffset() const {
    return offset;
}

const glm::vec3 &AABBCollider::getSize() const {
    return size;
}

float AABBCollider::getRadius() const {
    return radius;
}

bool AABBCollider::testRaycast(glm::vec3 origin, glm::vec3 direction) {
    return check2DRayCast(origin.x, origin.z, direction.x, direction.z,
                   this->min.x, this->max.x, this->min.z, this->max.z)
    && check2DRayCast(origin.x, origin.y, direction.x, direction.y,
                      this->min.x, this->max.x, this->min.y, this->max.y);
}

glm::vec3 AABBCollider::getCollisionInfo(AABBCollider *dst) {
    return glm::vec3(
            getAxisInfo(this->min.x, this->max.x, dst->min.x, dst->max.x),
            getAxisInfo(this->min.y, this->max.y, dst->min.y, dst->max.y),
            getAxisInfo(this->min.z, this->max.z, dst->min.z, dst->max.z)
    );
}

int AABBCollider::getAxisInfo(float minA, float maxA, float minB, float maxB) {
    if(minA >= minB && minA <= maxB) return 1;
    if(minB >= minA && minB <= maxA) return -1;
    return 0;
}

bool AABBCollider::isWall() const {
    return wall;
}

void AABBCollider::setWall(bool w) {
    wall = w;
}
