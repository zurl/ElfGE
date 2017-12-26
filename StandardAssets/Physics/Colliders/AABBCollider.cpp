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
    }
    allColliders.emplace_back(this);
    vertices.emplace_back(offset.x + size.x, offset.y + size.y, offset.z + size.z);
    vertices.emplace_back(offset.x - size.x, offset.y + size.y, offset.z + size.z);
    vertices.emplace_back(offset.x + size.x, offset.y - size.y, offset.z + size.z);
    vertices.emplace_back(offset.x - size.x, offset.y - size.y, offset.z + size.z);
    vertices.emplace_back(offset.x + size.x, offset.y + size.y, offset.z - size.z);
    vertices.emplace_back(offset.x - size.x, offset.y + size.y, offset.z - size.z);
    vertices.emplace_back(offset.x + size.x, offset.y - size.y, offset.z - size.z);
    vertices.emplace_back(offset.x - size.x, offset.y - size.y, offset.z - size.z);
    computeBox();
}

void AABBCollider::update() {
    computeBox();
    if (!passive) {
        for (auto &x : allColliders) {
            if (x != this) {
                bool isCollision = checkCollision(x);
                bool isOnCollision = onCollision.find(x) != onCollision.end();
                if (isCollision && !isOnCollision) {
                    onCollision.emplace(this);
                    auto result = this->getGameObject()->getComponents<GameScript>();
                    for (auto &y: result) {
                        y->onCollisionEnter(x);
                    }
                }
                if (!isCollision && isOnCollision) {
                    onCollision.erase(this);
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
                           bool passive
) : passive(passive), offset(offset), size(size) {
    for (auto &x: vertices) {
        min = glm::min(x, min);
        max = glm::max(x, max);
    }
}

bool AABBCollider::checkCollision(AABBCollider *dst) {
    return checkAxis(this->min.x, this->max.x, dst->min.x, dst->max.x)
           && checkAxis(this->min.y, this->max.y, dst->min.y, dst->max.y)
           && checkAxis(this->min.z, this->max.z, dst->min.z, dst->max.z);
}

bool AABBCollider::checkAxis(float minA, float maxA, float minB, float maxB) {
    return (minA >= minB && minA <= maxB) || (minB >= minA && minB <= maxA);
}

void AABBCollider::computeBox() {
    min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    max = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);
    for (auto &x: vertices) {
        glm::vec3 result =
                glm::rotate(getGameObject()->getWorldQuaternion(), x * getGameObject()->getWorldScale());
        min = glm::min(min, result);
        max = glm::max(max, result);
    }
    min += getGameObject()->getWorldPosition();
    max += getGameObject()->getWorldPosition();
}

AABBCollider::AABBCollider(bool passive) {
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
        target->computeBox();
        glm::vec3 pos = target->getGameObject()->getWorldPosition();
        float targetDis = glm::distance(origin, pos);
        if (targetDis < distance
            && check2DRayCast(origin.x, origin.z, direction.x, direction.z,
                              target->min.x, target->max.x, target->min.z, target->max.z)
            && check2DRayCast(origin.x, origin.y, direction.x, direction.y,
                              target->min.x, target->max.x, target->min.y, target->max.y)
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
