//
// Created by 张程易 on 31/10/2017.
//

#include "DirectLighting.h"

std::string DirectLighting::getName() {
    return "dirLight";
}

void DirectLighting::update(const std::string &prefix, Shader *shader) {
    shader->setVec3(prefix + "direction", getGameObject()->getWorldForward());
    shader->setVec3(prefix + "ambient", ambient);
    shader->setVec3(prefix + "diffuse", diffuse);
    shader->setVec3(prefix + "specular", specular);
}

DirectLighting::DirectLighting(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular) : ambient(
        ambient), diffuse(diffuse), specular(specular) {}
