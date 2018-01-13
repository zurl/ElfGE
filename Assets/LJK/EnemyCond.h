//
// Created by lulufa on 2017/12/17.
//

#ifndef ELFGE_ENEMYCOND_H
#define ELFGE_ENEMYCOND_H

#include "GameEngine.h"
#include "../LJK/AnimationCond.h"
#include <time.h>

class EnemyCond: public Component {
public:
    int Health;
    int Atk;
    GameObject *Human;
    float movespeed;
    const int interval = 300;

    float randX, randY;
    int timeCnt;



    EnemyCond(int health, int atk , GameObject *human)
            :Health(health),Atk(atk),Human(human){
        randX = (double)(rand()%100-50)/50;
        randY = (double)(rand()%100-50)/50;
        timeCnt = 0;
        movespeed = 0.1;


    }

    void die(){
        //EnemyGroup.remove(getGameObject());
        getGameObject()->getComponent<AnimationCond>()->play(6);

    }


    void move(){
        if(Health > 0) {

            glm::vec3 forward = getGameObject()->getWorldForward();
            glm::vec3 ToHuman = Human->getWorldPosition() - getGameObject()->getWorldPosition();
            double cos = (forward.x * ToHuman.x + forward.y * ToHuman.y + forward.z * ToHuman.z) /
                         (sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z) *
                          sqrt(ToHuman.x * ToHuman.x + ToHuman.y * ToHuman.y + ToHuman.z * ToHuman.z));

            if (ToHuman.x * ToHuman.x + ToHuman.z * ToHuman.z < 80) {
                getGameObject()->getComponent<AnimationCond>()->play(1);
                if (cos > 0.1) {
                    getGameObject()->transform.rotate(getGameObject()->getWorldUp(), 0.05);
                } else if (cos < -0.1) {
                    getGameObject()->transform.rotate(getGameObject()->getWorldUp(), -0.05);
                }
                else{
                    getGameObject()->getComponent<RigidBody>()->translate((movespeed * getGameObject()->getWorldRight()));
                }
            }
            else {
                getGameObject()->getComponent<AnimationCond>()->play(8);
                if (timeCnt > interval) {
                    timeCnt = 0;
                }

                if (timeCnt == 0) {
                    getGameObject()->transform.rotate(getGameObject()->getWorldUp(), (double)(rand()%100-50)/50);
                }
                getGameObject()->getComponent<RigidBody>()->translate((movespeed/2 * getGameObject()->getWorldRight()));

                timeCnt++;
            }
        }


        else{
            getGameObject()->getComponent<AnimationCond>()->play(6);
        }

    }
};


#endif //ELFGE_ENEMYCOND_H
