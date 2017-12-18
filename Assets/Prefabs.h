//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_PREFABS_H
#define ELFGE_PREFABS_H

#include <UI/Image.h>
#include "GameEngine.h"
#include "StandardAssets.h"
#include <random>
#include "Prefab/ScrollBar.h"
#include "Prefab/ImageButton.h"

namespace Prefabs {

    extern StandardMaterial material;

    class DirLight : public Prefab {
        glm::vec3 rotation;
    public:
        DirLight(const glm::vec3 &rotation) : rotation(rotation) {}

        GameObject *instantiate(Scene *scene) override {
            auto ret = scene->createGameObject()
                    ->createComponent<CubeMesh>("brickwall.jpg", "brickwall.jpg", "brickwall_normal.jpg")
                    ->createComponent<Renderer>(
                            &material, ShaderManager::getShader("light_with_directional_shadow"))
                    ->createComponent<DirectLighting>();
            ret->transform.setRotation(rotation);
            return ret;
        }
    };

    class PointLight : public Prefab {

        glm::vec3 position;
    public:
        PointLight(const glm::vec3 &position) : position(position) {}

        GameObject *instantiate(Scene *scene) override {
            auto result = scene->createGameObject()
                    ->createComponent<PointLighting>();
            result->transform.setPosition(position);
            return result;
        }
    };

    class Cube : public Prefab {
        glm::vec3 position;
    public:
        Cube(const glm::vec3 &position) : position(position) {}

        GameObject *instantiate(Scene *scene) override {

            auto result = scene->createGameObject()
                    ->createComponent<DefaultModel>(
                            new CubeMesh("bricks2.jpg", "bricks2.jpg", "bricks2_normal.jpg", "bricks2_disp.jpg"))
                    ->createComponent<Renderer>(
                            &material, ShaderManager::getShader("light_ds_pm"))
                    ->createComponent<AABBCollider>(false)
                    ->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1.0, false);

            result->transform.setPosition(position);
            return result;
        }
    };

    class Plane : public Prefab {
        glm::vec3 position;
    public:
        Plane(const glm::vec3 &position) : position(position) {}

        GameObject *instantiate(Scene *scene) override {

            auto result = scene->createGameObject()
//                    ->createComponent<DefaultModel>(new PlaneMesh("brickwall.jpg", "brickwall.jpg", "brickwall_normal.jpg"))
                    ->createComponent<DefaultModel>(new PlaneMesh("", "", ""))
                    ->createComponent<Renderer>(
                            nullptr, ShaderManager::getShader("simple"));
            result->transform.setPosition(position);
            return result;
        }
    };


    class Camera : public Prefab {
    public:
        GameObject *instantiate(Scene *scene) override {
            auto camera = scene->createGameObject()
                    ->createComponent<FirstPlayerCamera>();

            scene->setCamera(camera->getComponent<FirstPlayerCamera>());
            return camera;
        }
    };

    class DemoTerrain : public Prefab {
    public:
        GameObject *instantiate(Scene *scene) override {
            auto terrain = scene->createGameObject()
                    ->createComponent<Terrain>("heightMap.png", "brickwall.jpg", "brickwall_normal.jpg")
                    ->createComponent<Renderer>(
                            &material,
                            ShaderManager::getShader("light_with_directional_shadow")
                    );
            return terrain;
        }
    };



};

#endif //ELFGE_PREFABS_H
