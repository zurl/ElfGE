//
// Created by 张程易 on 29/10/2017.
//

#include "GameObject.h"

void GameObject::setParent(GameObject *parent) {
    if( parent == this->parent ) return;
    if( this->parent != nullptr ){
        this->parent->__detachChildren(this);
    }
    this->parent = parent;
    this->parent->__attachChildren(this);
}

void GameObject::__attachChildren(GameObject *gameObject) {
    children.emplace_back(gameObject);
}

void GameObject::__detachChildren(GameObject *gameObject) {
    children.remove(gameObject);
}

void GameObject::__detachComponent(Component *component) {
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
