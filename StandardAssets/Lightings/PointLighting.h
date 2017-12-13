//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_POINTLIGHTING_H
#define ELFGE_POINTLIGHTING_H

#include "GameEngine.h"

class PointLighting : public Lighting {

public:
    glm::vec3 ambient, diffuse, specular;
    float constant, linear, quadratic;

    PointLighting(const glm::vec3 &ambient = glm::vec3(0.05f, 0.05f, 0.05f),
                  const glm::vec3 &diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
                  const glm::vec3 &specular = glm::vec3(1.0f, 1.0f, 1.0f),
                  float constant = 1.0f,
                  float linear = 0.09f,
                  float quadratic = 0.032f);

    std::string getName() override;

    void update(const std::string &prefix, Shader *shader) override;
};


#endif //ELFGE_POINTLIGHTING_H
