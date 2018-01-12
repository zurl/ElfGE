//
// Created by 张程易 on 11/01/2018.
//

#ifndef ELFGE_ENVIRONMENT_H
#define ELFGE_ENVIRONMENT_H

#include "GameEngine.h"
#include "StandardAssets.h"
class Land: public Prefab{
    std::vector<std::string> names = {
            "GR_1_UV.png",
            "GR_2_UV.png",
            "bTex.jpg",
            "aTex.jpg",
            "GR_1_Normal.png",
            "GR_2_Normal.png",
            "Normal.jpg",
            "Normal.jpg",
            "heightmap.jpg"
    };

    static float myrand(float min, float max){
        float seed = rand() * 1.0f / RAND_MAX; // 0-1
        return min + seed * (max - min);
    }

    void createCollider(GameObject * parent, glm::vec3 size, glm::vec3 offset){
        auto obj = new GameObject("colliderwall");
        obj->createComponent<DefaultModel>(
                new CubeMesh("bricks2.jpg", "bricks2.jpg", "bricks2_normal.jpg", "bricks2_disp.jpg"))
            ->createComponent<Renderer>(
                    &material, ShaderManager::getShader("light_ds_pm"))
            ->createComponent<AABBCollider>(true);
        obj->transform.setPosition(offset);
        obj->transform.setScale(size);
        //obj->createComponent<AABBCollider>(size, offset, true, false);
        obj->setParent(parent);
    }

public:
    GameObject *instantiate(Scene *scene) override {
        srand((unsigned)time(NULL));
        auto terrainGO = scene->createGameObject("terrain")
                ->createComponent<Terrain>("heightMap.png","terrain/", names)
        ->createComponent<Renderer>(
                &material,
                ShaderManager::getShader("terrain/terrain")
        );

        auto grass = scene->createGameObject("grass")
                ->createComponent<GrassRenderer>(
                        Utility::RESOURCE_PREFIX + "Textures/grass/grass.jpg",
//                        Utility::RESOURCE_PREFIX + "Textures/grass/heightmap.jpg"
                        Utility::RESOURCE_PREFIX + "Textures/heightMap.png"
                );

        auto terrain = terrainGO->getComponent<Terrain>();


        auto house = scene->createGameObject()
                ->createComponent<DefaultModel>(Utility::RESOURCE_PREFIX + "Models/house/cabin.obj")
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("house/light_with_directional_shadow")
                );

        auto door = scene->createGameObject()
                ->createComponent<DoorModel>(Utility::RESOURCE_PREFIX + "Models/house/door.obj")
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("house/light_with_directional_shadow")
                )
                ->createComponent<AABBCollider>(true, false);
        door->setParent(house);
        door->transform.setScale(glm::vec3(1.1f,1.05f,1.0f));
        door->transform.setPosition(glm::vec3(2.6f,1.0f,2.2f));
        house->transform.setPosition(glm::vec3(0, terrain->getHeight(0, 0), 0));
        createCollider(house, glm::vec3(1.5f,5.0f,6.5f),glm::vec3(6.2f,3.0f,1.0f));
        createCollider(house, glm::vec3(1.5f,5.0f,6.5f),glm::vec3(-6.2f,3.0f,-1.0f));
        createCollider(house, glm::vec3(13.2f,4.6f,1.2f),glm::vec3(0,3.0f,-4.0f));
        createCollider(house, glm::vec3(1.7f,4.6f,1.2f),glm::vec3(-3.8,3.0f,1.9f));
        createCollider(house, glm::vec3(2.5f,4.6f,1.2f),glm::vec3(5.4f,3.0f,1.9f));


        for(int i = 0; i < 50; i ++){
            float x = myrand(-50, 50);
            float z = myrand(-50, 50);
            float y = terrain->getHeight(x, z);

            auto tree = scene->createLODGameObject()
                    ->createComponent<AABBCollider>(true, true)
            ->createComponent<DefaultModel>(
                    Utility::RESOURCE_PREFIX + "Models/tree/Tree.obj")
            ->createComponent<Renderer>(
                    StandardMaterial::getInstance(),
                    ShaderManager::getShader("light_with_directional_shadow")
            );

            tree->transform.setPosition(glm::vec3(x, y, z));

        }

        return terrainGO;
    }
};

#endif //ELFGE_ENVIRONMENT_H
