//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_TRANSFORM_H
#define ELFGE_TRANSFORM_H

#include "../Common.h"

class Transform {
    glm::vec3 position;
    glm::mat4 rotation;
    glm::vec3 scale;
    glm::vec3 lastAngle = glm::vec3(0.0f);
public:
    Transform();

    glm::mat4 getModelMatrix() const;

    const glm::vec3 &getLocalPosition() const;

    void setPosition(const glm::vec3 &position);

    void translate(const glm::vec3 &position);

    glm::vec3 getLocalRotation() const;

    void setRotation(const glm::vec3 &eularAngle);

    void setRotationEx(const glm::vec3 &eularAngle);

    glm::mat4 getLocalQuatMatrix() const;

    glm::quat getLocalQuaternion() const;

    const glm::vec3 &getLocalScale() const;

    void setScale(const glm::vec3 &scale);

    static glm::vec3 up, forward, right;

    glm::vec3 getLocalForward() const;

    glm::vec3 getLocalRight() const;

    glm::vec3 getLocalUp() const;

    void rotate(glm::vec3 axis, float angle);

};


#endif //ELFGE_TRANSFORM_H
