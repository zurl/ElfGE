//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEFAULTCAMERA_H
#define ELFGE_DEFAULTCAMERA_H

#include "Common.h"
#include "Utility.h"
#include "Camera.h"
#include "GameScript.h"

// Default camera values
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.002f;
const float ZOOM        =  45.0f;

class DefaultCamera : public Camera{
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
    glm::vec3 front;

    GLboolean constrainPitch = 1;


    enum class Direction{
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

public:

    // Constructor with vectors
    DefaultCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 front = glm::vec3(1.0f, 1.0f, 1.0f),
                  float zoom = ZOOM,
                  float sensitivity = SENSITIVITY,
                  float speed = SPEED
    );

    virtual glm::mat4 getViewMatrix() override ;

    virtual glm::mat4 getProjectionMatrix() override ;

private:

    void onMouseMove(double xoffset, double yoffset) override;

    void onScrollMove(double x) override;

    void start() override;

    void update() override;

};


#endif //ELFGE_DEFAULTCAMERA_H
