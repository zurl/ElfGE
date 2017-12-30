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
    if(this->parent != nullptr) this->parent->attachChildren(this);
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
    if (parent == nullptr) return transform.getModelMatrix();
    else return parent->getModelMatrix() * transform.getModelMatrix();
}

GameObject::GameObject(const std::string &name) : name(name) {}

const std::string &GameObject::getName() const {
    return name;
}

void GameObject::setName(const std::string &name) {
    GameObject::name = name;
}

const std::list<GameObject *> &GameObject::getChildren() const {
    return children;
}

const std::list<Component *> &GameObject::getComponents() const {
    return components;
}

glm::vec3 GameObject::getWorldPosition() const {
    if (parent == nullptr) return transform.getLocalPosition();
    else return transform.getLocalPosition() + parent->getWorldPosition();
}

glm::vec3 GameObject::getWorldScale() const {
    if (parent == nullptr) return transform.getLocalScale();
    else return transform.getLocalScale() * parent->getWorldScale();
}

glm::quat GameObject::getWorldQuaternion() const {
    if (parent == nullptr) return transform.getLocalQuaternion();
    else return parent->getWorldQuaternion() * transform.getLocalQuaternion();
}

glm::vec3 GameObject::getWorldForward() const {
    return glm::rotate(getWorldQuaternion(), Transform::forward);
}

glm::vec3 GameObject::getWorldUp() const {
    return glm::rotate(getWorldQuaternion(), Transform::up);
}

glm::vec3 GameObject::getWorldRight() const {
    return glm::rotate(getWorldQuaternion(), Transform::right);
}

glm::vec3 GameObject::getWorldRotation() const {
    return glm::eulerAngles(getWorldQuaternion());
}
