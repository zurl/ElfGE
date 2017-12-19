//
// Created by lulufa on 2017/12/19.
//

#ifndef ELFGE_ANIMATIONCOND_H
#define ELFGE_ANIMATIONCOND_H

#include <Models/AnimatedModel.h>
#include "GameEngine.h"

class AnimationCond: public Component {
public:
    int now;
    int previous;

    AnimationCond(){
        now = previous = 0;
        getGameObject()->getComponent<AnimatedModel>()->playAnimation("IDLE");
    }

    void play(int state){
        previous = now;
        now = state;
        if(now != previous){
            switch(now){
                case 0:
                    getGameObject()->getComponent<AnimatedModel>()->playAnimation("IDLE");
                    break;
                case 1:
                    getGameObject()->getComponent<AnimatedModel>()->playAnimation("RUN_WITH_GUN");
                    break;
            }
        }

    }

};


#endif //ELFGE_ANIMATIONCOND_H
