//
// Created by 张程易 on 30/10/2017.
//

#include "PointLighting.h"

std::string PointLighting::getName() {
    return "pointLight";
}

void PointLighting::update(const std::string &prefix, Shader *shader) {
    shader->setVec3(prefix + "position", getGameObject()->getWorldPosition());
    shader->setVec3(prefix + "ambient", ambient);
    shader->setVec3(prefix + "diffuse", diffuse);
    shader->setVec3(prefix + "specular", specular);
    shader->setFloat(prefix + "constant", constant);
    shader->setFloat(prefix + "linear", linear);
    shader->setFloat(prefix + "quadratic", quadratic);
}

PointLighting::PointLighting(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                             float constant, float linear, float quadratic) : ambient(ambient), diffuse(diffuse),
                                                                              specular(specular), constant(constant),
                                                                              linear(linear), quadratic(quadratic) {}
