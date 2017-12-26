//
// Created by 张程易 on 25/12/2017.
//

#include <Config.h>
#include "LODGameObject.h"
#include "Runtime.h"
#include "Camera.h"

LODGameObject::LODGameObject(const std::string &name) : GameObject(name) {}

void LODGameObject::update() {
    float dis = glm::distance(
            getWorldPosition(),
            Runtime::getCamera()->getGameObject()->getWorldPosition());
    if( dis < Config::LOD::hideDistance)
        GameObject::update();
}

void LODGameObject::updateGraphics(RenderLayer renderLayer) {
    float dis = glm::distance(
            getWorldPosition(),
            Runtime::getCamera()->getGameObject()->getWorldPosition());
    if( dis < Config::LOD::hideDistance)
        GameObject::updateGraphics(renderLayer);
}
