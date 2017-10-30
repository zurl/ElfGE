//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_INPUT_H
#define ELFGE_INPUT_H
#include "../Common.h"
#include "../Utility.h"

class Input {

    static std::list<std::function<void(double)>* > scrollEventHandlers;
    static std::list<std::function<void(double, double)>* > mouseEventHandlers;

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
        for( auto & handler : mouseEventHandlers ){
            (*handler)(xpos, ypos);
        }
    }

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        for( auto & handler : scrollEventHandlers){
            (*handler)(yoffset);
        }
    }

public:

    static void initialize(){
        glfwSetCursorPosCallback(Utility::window, mouseCallback);
        glfwSetScrollCallback(Utility::window, scrollCallback);
    }

    static void attachOnMouseMove(std::function<void(double, double)> * callback){
        mouseEventHandlers.emplace_back(callback);
    }

    static void attachOnScrollMove(std::function<void(double)> * callback){
        scrollEventHandlers.emplace_back(callback);
    }


    static void detachOnMouseMove(std::function<void(double, double)> *callback) {
        mouseEventHandlers.remove(callback);
    }

    static void detachOnScrollMove(std::function<void(double)> *callback) {
        scrollEventHandlers.remove(callback);
    }


};


#endif //ELFGE_INPUT_H
