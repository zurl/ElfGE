//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_DIRECTLIGHTING_H
#define ELFGE_DIRECTLIGHTING_H


#include "GameEngine.h"

class DirectLighting: public Lighting {
public:
    glm::vec3 ambient, diffuse, specular;
    DirectLighting(const glm::vec3 &ambient = glm::vec3(0.05f, 0.05f, 0.05f),
                   const glm::vec3 &diffuse = glm::vec3(1.4f, 1.4f, 1.4f),
                   const glm::vec3 &specular= glm::vec3(1.5f, 1.5f, 1.5f));

    std::string getName() override;

    void update(const std::string &prefix, Shader *shader) override;
};


#endif //ELFGE_DIRECTLIGHTING_H
