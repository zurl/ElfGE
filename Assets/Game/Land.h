//
// Created by 张程易 on 11/01/2018.
//

#ifndef ELFGE_ENVIRONMENT_H
#define ELFGE_ENVIRONMENT_H

#include "GameEngine.h"
#include "StandardAssets.h"
class Land: public Prefab{
    std::vector<std::string> names = {
            "rTex.jpg",
            "gTex.jpg",
            "bTex.jpg",
            "aTex.jpg",
            "Normal.jpg",
            "Normal.jpg",
            "Normal.jpg",
            "Normal.jpg",
            "heightmap.jpg"
    };

    static float myrand(float min, float max){
        float seed = rand() * 1.0f / RAND_MAX; // 0-1
        return min + seed * (max - min);
    }

public:
    GameObject *instantiate(Scene *scene) override {
        srand((unsigned)time(NULL));
        auto terrainGO = scene->createGameObject("terrain")
                ->createComponent<Terrain>("heightMap.png","terrain/", names);


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

        house->transform.setPosition(glm::vec3(10000, terrain->getHeight(0, 0), 0));

        auto water = scene->createGameObject()
                ->createComponent<WaterRenderer>();

        water->transform.translate(glm::vec3(0, 7, 0 ));


        for(int i = 0; i < 10; i ++){
            float x = myrand(-10, 10);
            float z = myrand(-10, 10);
            float y = terrain->getHeight(x, z);

            auto tree = scene->createLODGameObject()
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
