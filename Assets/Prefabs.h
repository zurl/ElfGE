//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_PREFABS_H
#define ELFGE_PREFABS_H

#include "../GameEngine/GameEngine.h"
#include "../StandardAssets/StandardAssets.h"

BlankMaterial material;

class Prefabs{

public:

    static GameObject * camera(Scene * scene) {
        auto camera =
                scene->createGameObject()
                ->createComponent<FPSCamera>();

        scene->setCamera(camera->getComponent<FPSCamera>());

        return camera;
    }

    static GameObject * cube(Scene * scene, glm::vec3 position = glm::vec3(0,0,0)){
        auto cube = scene->createGameObject()
                ->createComponent<DefaultModel>(new CubeMesh())
                ->createComponent<MeshRenderer>(
                        &material, ShaderManager::getShader("light"));

        cube->transform.translate(position);

        return cube;
    }
};

#endif //ELFGE_PREFABS_H
