//
// Created by 张程易 on 30/10/2017.
//

#include "Input.h"


std::list<std::function<void(double)>* > Input::scrollEventHandlers;
std::list<std::function<void(double, double)>* > Input::mouseEventHandlers;
