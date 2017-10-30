//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_GAMESCRIPT_H
#define ELFGE_GAMESCRIPT_H

#include "Component.h"
#include "Input.h"

class GameScript: public Component {
    std::function<void(double, double)> mouseHandler = nullptr;
    std::function<void(double)> scrollHandler = nullptr;
protected:
    void enableMouseInput(){
        mouseHandler = std::bind(&GameScript::onMouseMove, this);
        Input::attachOnMouseMove(&mouseHandler);
    }
    void enableScrollInput(){
        scrollHandler = std::bind(&GameScript::onScrollMove, this);
        Input::attachOnScrollMove(&scrollHandler);
    }
public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void onMouseMove(double x, double y){ }
    virtual void onScrollMove(double x){ }

    virtual ~GameScript() {
        if(mouseHandler != nullptr) Input::detachOnMouseMove(&mouseHandler);
        if(scrollHandler != nullptr) Input::detachOnScrollMove(&scrollHandler);
    }

};


#endif //ELFGE_GAMESCRIPT_H
