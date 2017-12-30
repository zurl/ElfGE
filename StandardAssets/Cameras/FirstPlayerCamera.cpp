//
// Created by 张程易 on 30/10/2017.
//

#include "FirstPlayerCamera.h"


void FirstPlayerCamera::update() {
    }

void FirstPlayerCamera::onMouseMove(double xpos, double ypos) {
    Utility::MOUSE_X = xpos;
    Utility::MOUSE_Y = ypos;

    static double lastY = Utility::SCREEN_HEIGHT / 2;

    double yoffset =  lastY - ypos;

    lastY = ypos;

    yoffset *= mouseSensitivity ;

    getGameObject()->transform.rotate(Transform::right, yoffset);
}

void FirstPlayerCamera::onScrollMove(double x) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= x;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

