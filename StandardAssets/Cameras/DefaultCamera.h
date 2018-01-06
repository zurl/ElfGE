//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_DEFAULTCAMERA_H
#define ELFGE_DEFAULTCAMERA_H

#include "GameEngine.h"


const float SPEED = 2.5f;
const float SENSITIVITY = 0.002f;
const float ZOOM = 45.0f;


class DefaultCamera : public Camera {
public:
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
    glm::vec3 front;
public:
    DefaultCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 front = glm::vec3(1.0f, 1.0f, 1.0f),
                  float zoom = ZOOM,
                  float sensitivity = SENSITIVITY,
                  float speed = SPEED
    );

    // Constructor with vectors
    virtual glm::mat4 getViewMatrix() override;

    virtual glm::mat4 getProjectionMatrix() override;

    void start() override;

};


#endif //ELFGE_DEFAULTCAMERA_H
