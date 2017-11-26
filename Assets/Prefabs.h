//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_PREFABS_H
#define ELFGE_PREFABS_H

#include "GameEngine.h"
#include "StandardAssets.h"

namespace Prefabs{

    extern StandardMaterial material;

    class DirLight: public Prefab{
        glm::vec3 rotation;
    public:
        DirLight(const glm::vec3 &rotation) : rotation(rotation) {}

        GameObject * instantiate(Scene *scene) override {
            auto ret = scene->createGameObject()
            ->createComponent<DefaultModel>(new CubeMesh("cube_specular.png", "cube_diffuse.png"))
            ->createComponent<Renderer>(
                    &material, ShaderManager::getShader("light_with_directional_shadow"))
            ->createComponent<DirectLighting>();
            ret->transform.setRotation(rotation);
            return ret;
        }
    };

    class PointLight: public Prefab{

        glm::vec3 position;
    public:
        PointLight(const glm::vec3 &position) : position(position) {}
        GameObject * instantiate(Scene *scene) override {
            auto result = scene->createGameObject()
                    ->createComponent<PointLighting>();
            result->transform.setPosition(position);
            return result;
        }
    };

    class Cube: public Prefab{
        glm::vec3 position;
    public:
        Cube(const glm::vec3 &position) : position(position) {}
        GameObject * instantiate(Scene *scene) override {
            auto result = scene->createGameObject()
                    ->createComponent<DefaultModel>(new CubeMesh("cube_specular.png", "cube_diffuse.png"))
                    ->createComponent<Renderer>(
                            &material, ShaderManager::getShader("light_with_directional_shadow"))
                    ->createComponent<AABBCollider>(false)
                    ->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1.0, false);

            result->transform.setPosition(position);
            return result;
        }
    };

    class Camera: public Prefab{
    public:
        GameObject * instantiate(Scene *scene) override {
            auto camera = scene->createGameObject()
                                   ->createComponent<FirstPlayerCamera>();

            scene->setCamera(camera->getComponent<FirstPlayerCamera>());
            return camera;
        }
    };
    class DemoTerrain: public Prefab{
    public:
        GameObject *instantiate(Scene *scene) override {
            auto terrain = scene->createGameObject()
                    ->createComponent<Terrain>(
                            Utility::RESOURCE_PREFIX + "Textures/" + "heightMap.png",
                            Utility::RESOURCE_PREFIX + "Textures/" + "terrainTexture.jpg")
                    ->createComponent<Renderer>(
                            &material,
                            ShaderManager::getShader("light_with_directional_shadow")
                    );
            return terrain;
        }
    };

};

#endif //ELFGE_PREFABS_H
