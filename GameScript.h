//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_GAMESCRIPT_H
#define ELFGE_GAMESCRIPT_H

#include "Component.h"
#include "Input.h"


class GameScript: public Component {
    std::function<void(double, double)> mouseHandler;
    std::function<void(double)> scrollHandler;
protected:
    void enableMouseInput(){
        mouseHandler = std::bind(&GameScript::onMouseMove,
                                 this,
                                 std::placeholders::_1,
                                 std::placeholders::_2
        );
        Input::attachOnMouseMove(&mouseHandler);
    }
    void enableScrollInput(){
        scrollHandler = std::bind(&GameScript::onScrollMove,
                                  this,
                                  std::placeholders::_1);
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
