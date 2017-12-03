//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_INPUT_H
#define ELFGE_INPUT_H
#include "../Common.h"
#include "Utility.h"

class Input {

    struct MouseClickHandler{
        double xl, xr, yl, yr;
        int priority;
        std::function<void()>* enterCallback, * exitCallback;

        MouseClickHandler(double xl, double xr, double yl, double yr, int priority,
                          std::function<void()> *enterCallback, std::function<void()> *exitCallback);
    };

    static std::list<std::function<void(double)>* > scrollEventHandlers;
    static std::list<std::function<void(double, double)>* > mouseEventHandlers;
    static std::list<MouseClickHandler> mouseClickEventHandlers;
    static MouseClickHandler * onClick;

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

public:

    static void initialize();

    static void attachOnMouseMove(std::function<void(double, double)> * callback);

    static void attachOnScrollMove(std::function<void(double)> * callback);


    static void detachOnMouseMove(std::function<void(double, double)> *callback);

    static void detachOnScrollMove(std::function<void(double)> *callback);

    static void attachOnMouseClick(double xl, double xr, double yl, double yr, double priority,
                                   std::function<void()> * enterCallback,
                                   std::function<void()> * exitCallback
    );

    static void detachOnMouseClick(std::function<void()> *callback);

    static void processClick();

};


#endif //ELFGE_INPUT_H
