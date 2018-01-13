//
// Created by 张程易 on 23/12/2017.
//

#ifndef ELFGE_DEVELOPERSCRIPT_H
#define ELFGE_DEVELOPERSCRIPT_H

#include "StandardAssets.h"
#include "GameEngine.h"
#include "UI/UI.h"
#include "../Prefab/PlainText.h"
#include "../Prefabs.h"
#include "../Game/UIManager.h"

using namespace Prefabs;

class DeveloperScript: public GameScript {
    Text * text1, * text2, * text3;
    std::function<void()> enter;
    bool enable = false;
    std::string status, components, state;
    int keyCounter = 0;
    Collider *x, *y, *z;
    int setType = 0, setAxis = 0;
    float len = 0.5;

    GameObject * UIRoot = nullptr;
    GameObject * human = nullptr;
    GameObject * target = nullptr;
    GameObject * light; // add by ljk
    GameObject * woodButton;
    GameObject * BrickButton;
    GameObject * MetalButton;
    GameObject * StoneButton;

    Component * shootScript;

    void updateText();

    void updateState();

    void adjust(float delta);

public:
    DeveloperScript(UIManager * uiManager, GameObject *human, GameObject * light);

private:

    //three bars add by ljk
    std::function<void(double)> oncg1;
    std::function<void(double)> oncg2;
    std::function<void(double)> oncg3;

    //four buttons add by ljk
    std::function<void()> onclk1;
    std::function<void()> onclk2;
    std::function<void()> onclk3;
    std::function<void()> onclk4;

    void onClickEnter();

    void start() override;

    void update() override;

};


#endif //ELFGE_DEVELOPERSCRIPT_H