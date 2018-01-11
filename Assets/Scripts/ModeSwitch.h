//
// Created by 张程易 on 11/01/2018.
//

#ifndef ELFGE_MODESWITCH_H
#define ELFGE_MODESWITCH_H

#include "GameEngine.h"

class ModeSwitch: public GameScript{

    int mode = 1;
    int mode_timer = 0;
public:
    void update() override {
        if(mode_timer > 0) mode_timer --;
        if (glfwGetKey(Utility::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            if(mode_timer == 0){
                if (mode == 0) {
                    mode = 1;
                    mode_timer = 50;
                    glfwSetInputMode(Utility::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
                else{
                    mode = 0;
                    mode_timer = 50;
                    glfwSetInputMode(Utility::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
            }
        }
    }

};

#endif //ELFGE_MODESWITCH_H
