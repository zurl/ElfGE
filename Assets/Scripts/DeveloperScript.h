//
// Created by 张程易 on 23/12/2017.
//

#ifndef ELFGE_DEVELOPERSCRIPT_H
#define ELFGE_DEVELOPERSCRIPT_H

#include "StandardAssets.h"
#include "GameEngine.h"
#include "UI/UI.h"

class DeveloperScript: public GameScript {
    Text * text1, * text2, * text3;
    std::function<void()> enter;
    bool enable = false;
    std::string status, components, state;
    int keyCounter = 0;
    GameObject * target = nullptr;
    GameObject * controller = nullptr;
    Collider *x, *y, *z;
    int setType = 0, setAxis = 0;
    float len = 0.5;
public:
    DeveloperScript(Text *text1, Text *text2, Text *text3, GameObject *controller);

    void onClickEnter();

    void start() override;

    void update() override;

    void updateText();

    void updateState();

    void adjust(float delta);

};


#endif //ELFGE_DEVELOPERSCRIPT_H