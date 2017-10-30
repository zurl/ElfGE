//
// Created by 张程易 on 30/10/2017.
//

#include "GameScript.h"

void GameScript::enableMouseInput() {
    mouseHandler = std::bind(&GameScript::onMouseMove,
                             this,
                             std::placeholders::_1,
                             std::placeholders::_2
    );
    Input::attachOnMouseMove(&mouseHandler);
}

void GameScript::enableScrollInput() {
    scrollHandler = std::bind(&GameScript::onScrollMove,
                              this,
                              std::placeholders::_1);
    Input::attachOnScrollMove(&scrollHandler);
}

void GameScript::destroy() {
    if(mouseHandler != nullptr) Input::detachOnMouseMove(&mouseHandler);
    if(scrollHandler != nullptr) Input::detachOnScrollMove(&scrollHandler);
}

