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
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class DefaultCamera : public Camera, GameScript{
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
                  glm::vec3 front = glm::vec3(0.0f, 1.0f, 0.0f),
                  float zoom = ZOOM,
                  float sensitivity = SENSITIVITY,
                  float speed = SPEED
    );

    virtual glm::mat4 getViewMatrix();

    virtual glm::mat4 getProjectionMatrix();

private:

    void onMouseMove(double xoffset, double yoffset) override {

        glm::vec3 rotation = getParent()->transform.getRotation();

        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        rotation.y   += xoffset;
        rotation.x += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            if (rotation.x > 89.0f)
                rotation.x = 89.0f;
            if (rotation.x < -89.0f)
                rotation.x = -89.0f;
        }

        getParent()->transform.setRotation(rotation);
    }

    void onScrollMove(double x) override {
        if (zoom >= 1.0f && zoom <= 45.0f)
            zoom -= x;
        if (zoom <= 1.0f)
            zoom = 1.0f;
        if (zoom >= 45.0f)
            zoom = 45.0f;
    }

};


#endif //ELFGE_DEFAULTCAMERA_H
