//
// Created by 张程易 on 12/01/2018.
//

#ifndef ELFGE_FOLLOWHUMAN_H
#define ELFGE_FOLLOWHUMAN_H

#include "GameEngine.h"

class FollowHuman: public GameScript{

    GameObject * human;
    glm::vec3 pos;
public:
    FollowHuman(GameObject *human, glm::vec3 pos) : human(human), pos(pos) {}

    void update() override {
        glm::vec3 now = human->getWorldPosition();
        getGameObject()->transform.setPosition( now + pos);
    }

};

#endif //ELFGE_FOLLOWHUMAN_H
