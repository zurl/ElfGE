//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_PREFABS_H
#define ELFGE_PREFABS_H

#include "../GameEngine/ELFGE.h"
#include "../StandardAssets/Meshs/CubeMesh.h"

DefaultMaterial material;

class Prefabs{

public:

    static GameObject * camera(Scene * scene) {
        auto camera =
                scene->createGameObject()
                ->createComponent<DefaultCamera>();

        scene->setCamera(camera->getComponent<DefaultCamera>());

        return camera;
    }

    static GameObject * cube(Scene * scene, glm::vec3 position = glm::vec3(0,0,0)){
        auto cube = scene->createGameObject()
                ->createComponent<DefaultModel>(new CubeMesh())
                ->createComponent<MeshRenderer>(
                        &material, ShaderManager::getShader("simple"));

        cube->transform.translate(position);

        return cube;
    }
};

#endif //ELFGE_PREFABS_H
