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
    Collider *x, *y, *z;
    int setType = 0, setAxis = 0;
    float len = 0.5;
    GameObject * UIRoot = nullptr;

    void updateText();

    void updateState();

    void adjust(float delta);

public:
    DeveloperScript();

    void onClickEnter();

    void start() override;

    void update() override;

    GameObject *getUIRoot() const;
};


#endif //ELFGE_DEVELOPERSCRIPT_H