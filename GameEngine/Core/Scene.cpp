//
// Created by 张程易 on 29/10/2017.
//

#include "Scene.h"
#include "LODGameObject.h"

Camera *Scene::getCamera() const {
    return camera;
}

void Scene::setCamera(Camera *camera) {
    Scene::camera = camera;
}

Scene::~Scene() {
    destroy();
    delete rootGameObject;
    if (shadowMappingManager != nullptr) delete shadowMappingManager; // ?
}

void Scene::addGameObject(GameObject *gameObject) {
    gameObject->setParent(rootGameObject);
}

Scene::Scene() {
    rootGameObject = new GameObject("");
}

GameObject *Scene::createGameObject(const std::string & name) {
    GameObject *gameObject = new GameObject(name);
    addGameObject(gameObject);
    return gameObject;
}

GameObject *Scene::createLODGameObject(const std::string & name) {
    GameObject *gameObject = new LODGameObject(name);
    addGameObject(gameObject);
    return gameObject;
}

void Scene::destroy() {
    rootGameObject->destroy();
}


extern std::set<GameObject *> DestroyQueue;

void Scene::update() {
    rootGameObject->update();
    if(!DestroyQueue.empty()){
        for(GameObject * obj : DestroyQueue){
            obj->setParent(nullptr);
        }
        DestroyQueue.clear();
    }
}

void Scene::updateGraphics(RenderLayer renderLayer) {
    ShaderManager::useShader(nullptr);
    rootGameObject->updateGraphics(renderLayer);
}

void Scene::start() {
    rootGameObject->start();
}

ShadowMappingManager *Scene::getShadowMappingManager() const {
    return shadowMappingManager;
}

void Scene::setShadowMappingManager(ShadowMappingManager *shadowMappingManager) {
    Scene::shadowMappingManager = shadowMappingManager;
}
