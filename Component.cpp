//
// Created by 张程易 on 29/10/2017.
//

#include "Component.h"

GameObject *Component::getParent() const {
    return parent;
}

void Component::__setParent(GameObject *parent) {
    Component::parent = parent;
}
