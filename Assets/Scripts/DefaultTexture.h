//
// Created by lulufa on 2018/1/13.
//

#ifndef ELFGE_DEFAULTTEXTURE_H
#define ELFGE_DEFAULTTEXTURE_H

#include "StandardAssets.h"
#include "GameEngine.h"


class DefaultTexture : public GameScript{

public:

    void start() override {
        getGameObject()->getComponent<DefaultModel>()->meshes[0]->textures.emplace_back(
                TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/bricks2.jpg"),
                "diffuse"
        );
    }

    void update() override {

    }

};

#endif //ELFGE_DEFAULTTEXTURE_H
