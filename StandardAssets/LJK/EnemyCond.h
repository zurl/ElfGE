//
// Created by lulufa on 2017/12/17.
//

#ifndef ELFGE_ENEMYCOND_H
#define ELFGE_ENEMYCOND_H

#include "GameEngine.h"

class EnemyCond {
public:
    int Health;
    int Atk;
    EnemyCond(int health, int atk):Health(health),Atk(atk){}
};


#endif //ELFGE_ENEMYCOND_H
