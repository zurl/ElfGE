//
// Created by 张程易 on 29/10/2017.
//

#include "Transform.h"

glm::vec3 Transform::up(0, 1, 0);
glm::vec3 Transform::forward(1, 0, 0);
glm::vec3 Transform::right(0, 0, 1);


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

void Transform::setRotationEx(const glm::vec3 &eularAngle) {
    glm::vec3 delta = eularAngle - lastAngle;
    if( fabs(delta.x) > 1e-3 )rotate(Transform::forward, delta.x);
    if( fabs(delta.y) > 1e-3 )rotate(Transform::up, delta.y);
    if( fabs(delta.z) > 1e-3 )rotate(Transform::right, delta.z);
    lastAngle = eularAngle;
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

glm::quat Transform::getQuaternion() const {
    return glm::quat_cast(rotation);
}

Transform::Transform() : position(0.0f), rotation(1.0f), scale(1.0f) {}

glm::vec3 Transform::getUp() const {
    return glm::rotate(getQuaternion(), Transform::up);
}

glm::vec3 Transform::getRight() const {
    return glm::rotate(getQuaternion(), Transform::right);
}

glm::vec3 Transform::getForward() const {
    return glm::rotate(getQuaternion(), Transform::forward);
}

void Transform::rotate(glm::vec3 axis, float angle) {
    rotation = glm::toMat4(glm::rotate(getQuaternion(), angle, axis));
}

