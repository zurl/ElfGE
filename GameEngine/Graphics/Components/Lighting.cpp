//
// Created by 张程易 on 30/10/2017.
//

#include "Lighting.h"
#include "Graphics/LightingManager.h"


void Lighting::start() {
    LightingManager::attachLighting(getName(), this);
}

void Lighting::destroy() {
    LightingManager::detachLighting(getName(), this);
}

void Lighting::update() {

}
