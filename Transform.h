//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_TRANSFORM_H
#define ELFGE_TRANSFORM_H

#include "Common.h"

class Transform {
    glm::vec3 position;
    glm::mat4 rotation;
    glm::vec3 scale;
public:
    glm::mat4 getModelMatrix(glm::mat4 model) const;

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    void translate(const glm::vec3 &position);

    glm::vec3 getRotation() const;

    void setRotation(const glm::vec3 &eularAngle);

    glm::mat4 getQuatMatrix() const;

    const glm::vec3 &getScale() const;

    void setScale(const glm::vec3 &scale);

    static glm::vec3 up, forward, left;
};


#endif //ELFGE_TRANSFORM_H
