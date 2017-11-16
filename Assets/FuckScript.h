//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_FUCKSCRIPT_H
#define ELFGE_FUCKSCRIPT_H

#include "GameEngine.h"

class FuckScript: public GameScript {

public:
    void start() override;

    void update() override;

    void onCollisionEnter(Collider *collider) override;

    void onCollisionExit(Collider *collider) override;

};


#endif //ELFGE_FUCKSCRIPT_H
