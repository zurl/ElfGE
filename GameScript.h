//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_GAMESCRIPT_H
#define ELFGE_GAMESCRIPT_H

#include "Component.h"

class GameScript: public Component {
protected:

public:
    virtual void start() = 0;
    virtual void update() = 0;
};


#endif //ELFGE_GAMESCRIPT_H
