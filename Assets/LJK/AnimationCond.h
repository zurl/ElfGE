
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
    int timeforplay;
    bool die;
    AnimationCond(){
        now = previous = timeforplay = 0;
        die = false;
        //getGameObject()->getComponent<AnimatedModel>()->playAnimation("IDLE");
    }

    void play(int state){
        if(timeforplay == 0){
            if(die){
                printf("hello!");
                GameObject::destroy(getGameObject());
            }
            previous = now;
            now = state;
            if(now != previous){
                switch(now){
                    case 0:
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("IDLE");
                        break;
                    case 1:
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("RUN");
                        break;
                    case 2:
                        timeforplay = 30;
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("JUMP");
                        break;
                    case 3:
                        timeforplay = 200;
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("SHOOT");
                        break;
                    case 4:
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("DOWN");
                        break;
                    case 5:
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("RUN_DOWN");
                        break;
                    case 6:
                        timeforplay = 40;
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("DIE");
                        die = true;
                        break;
                    case 7:
                        timeforplay = 40;
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("HIT");
                        break;
                    case 8:
                        getGameObject()->getComponent<AnimatedModel>()->playAnimation("WALK");
                        break;

                }
            }
        }
        else{
            timeforplay--;
        }
    }

};


#endif //ELFGE_ANIMATIONCOND_H
