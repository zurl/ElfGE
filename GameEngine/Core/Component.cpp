//
// Created by 张程易 on 29/10/2017.
//

#include "Component.h"

GameObject *Component::getGameObject() const {
    return gameObject;
}

void Component::__setGameObject(GameObject *parent) {
    Component::gameObject = parent;
}

void Component::start() {

}

void Component::destroy() {
}

void Component::update() {

}

Component::~Component() {

}