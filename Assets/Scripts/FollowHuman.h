//
// Created by 张程易 on 12/01/2018.
//

#ifndef ELFGE_FOLLOWHUMAN_H
#define ELFGE_FOLLOWHUMAN_H

#include "GameEngine.h"

class FollowHuman: public GameScript{

    GameObject * human;
public:

    FollowHuman(GameObject *human) : human(human) {}

    void update() override {
        glm::vec3 now = human->getWorldPosition();
        getGameObject()->transform.setPosition( now - 3.0f * getGameObject()->getWorldForward());
    }

};

#endif //ELFGE_FOLLOWHUMAN_H
