//
// Created by 张程易 on 11/01/2018.
//

#ifndef ELFGE_KEEPHEIGHT_H
#define ELFGE_KEEPHEIGHT_H

#include "GameEngine.h"
#include "StandardAssets.h"

class KeepHeight: public GameScript{

    Terrain * terrain;

public:
    KeepHeight(Terrain *terrain) : terrain(terrain) {}

    void update() override {
        float x = getGameObject()->transform.getLocalPosition().x;
        float z = getGameObject()->transform.getLocalPosition().z;

        getGameObject()->transform.
                setPosition(
                glm::vec3(x, terrain->getHeight(x, z), z)
        );
    }
};

#endif //ELFGE_KEEPHEIGHT_H
