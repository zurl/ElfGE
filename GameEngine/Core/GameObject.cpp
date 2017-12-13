//
// Created by 张程易 on 29/10/2017.
//

#include "GameObject.h"

void GameObject::setParent(GameObject *parent) {
    if (parent == this->parent) return;
    if (this->parent != nullptr) {
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
    for (auto &x : components) {
        delete x;
    }
    for (auto &x : children) {
        delete x;
    }
}

void GameObject::update() {
    for (auto &x : components) {
        x->update();
    }
    for (auto &x : children) {
        x->update();
    }
}

void GameObject::updateGraphics(RenderLayer renderLayer) {
    for (auto &x : components) {
        x->updateGraphics(renderLayer);
    }
    for (auto &x : children) {
        x->updateGraphics(renderLayer);
    }
}

void GameObject::start() {
    for (auto &x : components) {
        x->start();
    }
    for (auto &x : children) {
        x->start();
    }
}

void GameObject::destroy() {
    for (auto &x : components) {
        x->destroy();
        detachComponent(x);
    }
    for (auto &x : children) {
        x->destroy();
    }
    if (parent != nullptr) {
        parent->detachChildren(this);
    }
}

void GameObject::destroy(GameObject *gameObject) {
    gameObject->destroy();
    delete gameObject;
}

void GameObject::destroy(Component *component) {
    component->destroy();
    delete component;
}

glm::mat4 GameObject::getModelMatrix() {
    if (parent == nullptr) return transform.getModelMatrix(glm::mat4(1.0f));
    else return transform.getModelMatrix(parent->getModelMatrix());
}
