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
    destroy();
    delete rootGameObject;
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

void Scene::destroy() {
    rootGameObject->destroy();
}

void Scene::update() {
    ShaderManager::useShader(nullptr);
    rootGameObject->update();
}

void Scene::start() {
    rootGameObject->start();
}
