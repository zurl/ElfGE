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
    const int interval = 100;

    float randX, randY;
    int timeCnt;

    //std::list<GameObject *> EnemyGroup;

    EnemyCond(int health, int atk , GameObject *human)
            :Health(health),Atk(atk),Human(human){
        randX = (double)(rand()%100-50)/50;
        randY = (double)(rand()%100-50)/50;
        timeCnt = 0;
        movespeed = 0.02;
        printf("fuck1\n");
        //group.push_back(getGameObject());
        printf("fuck2\n");

    }

    void die(){
        //EnemyGroup.remove(getGameObject());
        //GameObject::destroy(getGameObject());
        getGameObject()->setParent(NULL);
        //getGameObject()->destroy();

    }


    void move(){

        getGameObject()->getComponent<AnimationCond>()->play(1);
        //Human->transform.getLocalPosition()
        glm::vec3 dis = Human->getWorldPosition() - getGameObject()->getWorldPosition();
        if(dis.x * dis.x + dis.z * dis.z < 10){
            getGameObject()->transform.translate(movespeed * (Human->getWorldPosition() - getGameObject()->getWorldPosition()));
        }

        else{
            if(timeCnt > interval){
                timeCnt = 0;
            }

            if(timeCnt == 0){
                randX = (double)(rand()%100-50)/50;
                randY = (double)(rand()%100-50)/50;
            }

            //printf("%d %d\n", randX, randY);

            getGameObject()->getComponent<RigidBody>()->translate((movespeed * glm::vec3(randX,0,randY)));
//            getGameObject()->transform.translate(movespeed * glm::vec3(randX,0,randY));
            timeCnt ++;
        }
    }
};


#endif //ELFGE_ENEMYCOND_H
