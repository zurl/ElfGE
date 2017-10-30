//
// Created by 张程易 on 29/10/2017.
//

#include "Transform.h"

glm::vec3 Transform::up(0, 1, 0);
glm::vec3 Transform::forward(0, 0, 1);
glm::vec3 Transform::left(1, 0, 0);


glm::mat4 Transform::getModelMatrix(glm::mat4 model) const {
    model = glm::translate(model, position);
    model = model * rotation;
    model = glm::scale(model, scale);
    return model;
}

const glm::vec3 &Transform::getPosition() const {
    return position;
}

void Transform::setPosition(const glm::vec3 &position) {
    Transform::position = position;
}

glm::vec3 Transform::getRotation() const {
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

void Transform::translate(const glm::vec3 &position) {
    Transform::position += position;
}

glm::mat4 Transform::getQuatMatrix() const {
    return rotation;
}

