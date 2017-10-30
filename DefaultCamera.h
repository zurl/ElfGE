//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEFAULTCAMERA_H
#define ELFGE_DEFAULTCAMERA_H

#include "Common.h"
#include "Utility.h"
#include "Camera.h"

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class DefaultCamera : public Camera{
    // Vectors
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // Eular Angles
    float yaw;
    float pitch;
    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    GLboolean constrainPitch = 1;
public:

    // Constructor with vectors
    DefaultCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                  float yaw = YAW,
                  float pitch = PITCH,
                  float zoom = ZOOM,
                  float sensitivity = SENSITIVITY,
                  float speed = SPEED
    );

    virtual glm::mat4 getViewMatrix();

    virtual glm::mat4 getProjectionMatrix();

    virtual void processKeyboard(Direction direction, float deltaTime);

    virtual void processMouseMovement(float xoffset, float yoffset);

    virtual void processMouseScroll(float yoffset);

private:
    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();
};


#endif //ELFGE_DEFAULTCAMERA_H
