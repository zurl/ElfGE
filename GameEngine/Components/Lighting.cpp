//
// Created by 张程易 on 30/10/2017.
//

#include "Lighting.h"

void Lighting::start() {
    LightingManager::attachLighting(getName(), this);
}

void Lighting::update() {

}

Lighting::~Lighting() {
    LightingManager::detachLighting(getName(), this);
}
