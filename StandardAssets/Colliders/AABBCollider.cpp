//
// Created by 张程易 on 31/10/2017.
//

#include "AABBCollider.h"
#include "../Models/DefaultModel.h"

std::list<AABBCollider *> AABBCollider::allColliders;

void AABBCollider::start() {
    if( autogen ){
        autogen = false;
        min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
        max = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);
        auto model = getGameObject()->getComponent<DefaultModel>();
        if( model == nullptr ) throw Exception("AutoGen Only Support Default Mesh");
        for(auto & mesh : model->meshes){
            if( mesh == nullptr ) throw Exception("AutoGen Only Support Default Mesh");
            for(auto & vertex : mesh->vertices){
                min = glm::min(vertex.position, min);
                max = glm::max(vertex.position, max);
            }
        }
        offset = (min + max) * 0.5f * getGameObject()->transform.getScale();
        size = (max - min) * 0.5f * getGameObject()->transform.getScale();
        printf("of=%f %f %f\n", offset.x, offset.y, offset.z);
        printf("sz=%f %f %f\n", size.x, size.y, size.z);
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
    computerBox();
}

void AABBCollider::update() {
    computerBox();
    if( ! passive ){
        for(auto & x : allColliders ){
            if( x != this ){
                bool isCollision = checkCollision(x);
                bool isOnCollision = onCollision.find(x) != onCollision.end();
                if(isCollision && !isOnCollision){
                    onCollision.emplace(this);
                    auto result = this->getGameObject()->getComponents<GameScript>();
                    for(auto & y: result){
                        y->onCollisionEnter(x);
                    }
                }
                if(!isCollision && isOnCollision){
                    onCollision.erase(this);
                    auto result = this->getGameObject()->getComponents<GameScript>();
                    for(auto & y: result){
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
):passive(passive),offset(offset), size(size) {

}

bool AABBCollider::checkCollision(AABBCollider *dst) {
    return checkAxis(this->min.x, this->max.x, dst->min.x, dst->max.x)
           && checkAxis(this->min.y, this->max.y, dst->min.y, dst->max.y)
           && checkAxis(this->min.z, this->max.z, dst->min.z, dst->max.z);
}

bool AABBCollider::checkAxis(float minA, float maxA, float minB, float maxB) {
    return (minA >= minB && minA <= maxB) || (minB >= minA && minB <= maxA);
}

void AABBCollider::computerBox() {
    min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    max = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);
    for(auto & x: vertices){
        glm::vec3 result = glm::rotate(getGameObject()->transform.getQuaternion(), x);
        min = glm::min(min, result);
        max = glm::max(max, result);
    }
    min += getGameObject()->transform.getPosition();
    max += getGameObject()->transform.getPosition();
}

AABBCollider::AABBCollider(bool passive) {
    autogen = true;
}
