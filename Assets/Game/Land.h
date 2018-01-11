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
public:
    GameObject *instantiate(Scene *scene) override {

        auto terrain = scene->createGameObject("terrain")
                ->createComponent<Terrain>("heightMap.png","terrain/", names)
                ->createComponent<Renderer>(
                        StandardMaterial::getInstance(),
                        ShaderManager::getShader("terrain/terrain")
                );

        auto grass = scene->createGameObject("grass")
                ->createComponent<GrassRenderer>(
                        Utility::RESOURCE_PREFIX + "Textures/grass/grass.jpg",
//                        Utility::RESOURCE_PREFIX + "Textures/grass/heightmap.jpg"
                        Utility::RESOURCE_PREFIX + "Textures/heightMap.png"
                );

        return terrain;
    }
};

#endif //ELFGE_ENVIRONMENT_H
