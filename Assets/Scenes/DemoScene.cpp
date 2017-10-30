//
// Created by 张程易 on 30/10/2017.
//

#include "DemoScene.h"

void DemoScene::start() {

    auto camera = createGameObject()
            ->createComponent<DefaultCamera>();

    auto cube = createGameObject()
            ->createComponent<DefaultModel>(new CubeMesh())
            ->createComponent<MeshRenderer>(&material, ShaderManager::getShader("simple"));

    setCamera(camera->getComponent<DefaultCamera>());

    cube->transform.translate(glm::vec3(5, 0, 0));

    Scene::start();
}

void DemoScene::update() {
    Scene::update();
}

DemoScene::DemoScene(){}
