//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_FUCKSCRIPT_H
#define ELFGE_FUCKSCRIPT_H

#include "GameEngine.h"
#include "UI/UI.h"

class FuckScript : public GameScript {
    int cnt = 0;
    Text *text;
    GameObject *human;
    std::function<void()> cb;
public:

    void onClick();

    FuckScript(GameObject *human);

    void start() override;

    void update() override;

};


#endif //ELFGE_FUCKSCRIPT_H
