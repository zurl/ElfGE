//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_CAMERA_H
#define ELFGE_CAMERA_H

#include "Common.h"
#include "GameObject.h"

class Camera{
public:
    virtual glm::mat4 getViewMatrix() = 0;

    virtual glm::mat4 getProjectionMatrix() = 0;
};


#endif //ELFGE_CAMERA_H
