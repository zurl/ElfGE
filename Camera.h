//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_CAMERA_H
#define ELFGE_CAMERA_H

#include "Common.h"

class Camera {
public:
    enum class Direction{
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    virtual glm::mat4 getViewMatrix() = 0;

    virtual glm::mat4 getProjectionMatrix() = 0;

    virtual void processKeyboard(Direction direction, float deltaTime) = 0;

    virtual void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) = 0;

    virtual void processMouseScroll(float yoffset) = 0;
};


#endif //ELFGE_CAMERA_H
