//
// Created by 张程易 on 29/10/2017.
//

#include "Scene.h"

Camera *Scene::getCamera() const {
    return camera;
}

void Scene::setCamera(Camera *camera) {
    Scene::camera = camera;
}

Scene::~Scene() {
    GameObject::destroy(rootGameObject);
}

void Scene::addGameObject(GameObject *gameObject) {
    gameObject->setParent(rootGameObject);
}

Scene::Scene() {
    rootGameObject = new GameObject();
}

GameObject *Scene::createGameObject() {
    GameObject * gameObject = new GameObject();
    addGameObject(gameObject);
    return gameObject;
}
