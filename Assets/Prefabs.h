//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_PREFABS_H
#define ELFGE_PREFABS_H

#include "GameEngine.h"
#include "StandardAssets.h"

StandardMaterial material;

class Prefabs{

public:

    static GameObject * dirLight(Scene * scene, glm::vec3 rotation){

        auto light =
                scene->createGameObject()
                        ->createComponent<DefaultModel>(new CubeMesh("cube_specular.png", "cube_diffuse.png"))
                        ->createComponent<Renderer>(
                                &material, ShaderManager::getShader("light_with_omnidirectional_shadow"))

        ->createComponent<DirectLighting>();

        light->transform.setRotation(rotation);

        return light;
    }

    static GameObject * pointLight(Scene * scene, glm::vec3 position){

        auto light =
                scene->createGameObject()
                ->createComponent<PointLighting>();

        light->transform.translate(position);

        return light;
    }

    static GameObject * camera(Scene * scene) {
        auto camera =
                scene->createGameObject()
                ->createComponent<FirstPlayerCamera>();

        scene->setCamera(camera->getComponent<FirstPlayerCamera>());

        return camera;
    }

    static GameObject * cube(Scene * scene, glm::vec3 position = glm::vec3(0,0,0)){
        auto cube = scene->createGameObject()
                ->createComponent<DefaultModel>(new CubeMesh("cube_specular.png", "cube_diffuse.png"))
                ->createComponent<Renderer>(
                        &material, ShaderManager::getShader("light_with_omnidirectional_shadow"));

        cube->transform.translate(position);

        return cube;
    }
};

#endif //ELFGE_PREFABS_H
