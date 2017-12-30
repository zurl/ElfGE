//
// Created by 张程易 on 30/10/2017.
//

#include "Input.h"


std::list<std::function<void(double)> *> Input::scrollEventHandlers;
std::list<std::function<void(double, double)> *> Input::mouseEventHandlers;
std::list<Input::MouseClickHandler> Input::mouseClickEventHandlers;
Input::MouseClickHandler *Input::onClick = nullptr;

void Input::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    for (auto &handler : mouseEventHandlers) {
        (*handler)(xpos, ypos);
    }
}

void Input::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    for (auto &handler : scrollEventHandlers) {
        (*handler)(yoffset);
    }
}

void Input::initialize() {
    glfwSetCursorPosCallback(Utility::window, mouseCallback);
    glfwSetScrollCallback(Utility::window, scrollCallback);
    onClick = nullptr;
}

void Input::attachOnMouseMove(std::function<void(double, double)> *callback) {
    mouseEventHandlers.emplace_back(callback);
}

void Input::attachOnScrollMove(std::function<void(double)> *callback) {
    scrollEventHandlers.emplace_back(callback);
}

void Input::detachOnMouseMove(std::function<void(double, double)> *callback) {
    mouseEventHandlers.remove(callback);
}

void Input::detachOnScrollMove(std::function<void(double)> *callback) {
    scrollEventHandlers.remove(callback);
}

void
Input::attachOnMouseClick(double xl, double xr, double yl, double yr, double priority,
                          std::function<void()> *enterCallback,
                          std::function<void()> *exitCallback
) {
    mouseClickEventHandlers.emplace_back(
            xl, xr, yl, yr, priority, enterCallback, exitCallback
    );
}

void Input::detachOnMouseClick(std::function<void()> *enterCallback) {
    auto iter = mouseClickEventHandlers.begin();
    while (iter != mouseClickEventHandlers.end()) {
        if (iter->enterCallback == enterCallback) {
            mouseClickEventHandlers.erase(iter);
            return;
        }
        iter++;
    }
}

void Input::processClick() {
    bool isPressed = glfwGetMouseButton(Utility::window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
    if (isPressed && onClick == nullptr) {
        // Enter
        double x = Utility::MOUSE_X, y = Utility::SCREEN_HEIGHT - Utility::MOUSE_Y;
        MouseClickHandler *result = nullptr;
        for (auto &h : mouseClickEventHandlers) {
            if (h.xl <= x && h.xr >= x && h.yl <= y && h.yr >= y) {
                if (result == nullptr || h.priority > result->priority) {
                    result = &h;
                }
            }
        }
        if (result != nullptr) {
            onClick = result;
            if (result->enterCallback)result->enterCallback->operator()();
        }
    }
    if (!isPressed && onClick != nullptr) {
        if (onClick->exitCallback)onClick->exitCallback->operator()();
        onClick = nullptr;
    }
}

Input::MouseClickHandler::MouseClickHandler(double xl, double xr, double yl, double yr, int priority,
                                            std::function<void()> *enterCallback,
                                            std::function<void()> *exitCallback) : xl(xl), xr(xr), yl(yl), yr(yr),
                                                                                   priority(priority),
                                                                                   enterCallback(enterCallback),
                                                                                   exitCallback(exitCallback) {}
