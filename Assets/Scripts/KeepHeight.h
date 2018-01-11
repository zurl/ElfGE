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
        glm::vec3 pos = getGameObject()->transform.getLocalPosition();
        pos.z = terrain->getHeight(pos.x, pos.z);
        getGameObject()->transform.setPosition(pos);
    }
};

#endif //ELFGE_KEEPHEIGHT_H
