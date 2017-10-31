//
// Created by 张程易 on 29/10/2017.
//

#include "GameObject.h"

void GameObject::setParent(GameObject *parent) {
    if( parent == this->parent ) return;
    if( this->parent != nullptr ){
        this->parent->detachChildren(this);
    }
    this->parent = parent;
    this->parent->attachChildren(this);
}

void GameObject::attachChildren(GameObject *gameObject) {
    children.emplace_back(gameObject);
}

void GameObject::detachChildren(GameObject *gameObject) {
    children.remove(gameObject);
}

void GameObject::detachComponent(Component *component) {
    components.remove(component);
}

GameObject::~GameObject() {
    for(auto &x : components){
        delete x;
    }
    for(auto &x : children){
        delete x;
    }
}
