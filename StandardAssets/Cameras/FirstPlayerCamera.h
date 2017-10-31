//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_FPCAMERA_H
#define ELFGE_FPCAMERA_H

#include "DefaultCamera.h"


class FirstPlayerCamera : public DefaultCamera{

public:
    enum class Direction{
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    void onMouseMove(double xoffset, double yoffset) override;

    void onScrollMove(double x) override;

    void update() override;

};


#endif //ELFGE_FPSCAMERA_H
