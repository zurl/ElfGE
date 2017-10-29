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
    glm::mat4 transform(glm::mat4 trans) const;

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getRotation() const;

    void setRotation(const glm::vec3 &eularAngle);

    const glm::vec3 &getScale() const;

    void setScale(const glm::vec3 &scale);

};


#endif //ELFGE_TRANSFORM_H
