//
// Created by 张程易 on 29/10/2017.
//

#include "Transform.h"

glm::mat4 Transform::transform(glm::mat4 trans) const {
    trans = glm::translate(trans, position);
    trans = trans * rotation;
    trans = glm::scale(trans, scale);
    return trans;
}

const glm::vec3 &Transform::getPosition() const {
    return position;
}

void Transform::setPosition(const glm::vec3 &position) {
    Transform::position = position;
}

const glm::vec3 &Transform::getRotation() const {

    return glm::eulerAngles(glm::quat_cast(rotation));
}

void Transform::setRotation(const glm::vec3 &eularAngle) {
    rotation = glm::toMat4(glm::quat(eularAngle));
}

const glm::vec3 &Transform::getScale() const {
    return scale;
}

void Transform::setScale(const glm::vec3 &scale) {
    Transform::scale = scale;
}
