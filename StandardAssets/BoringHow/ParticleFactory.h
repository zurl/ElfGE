//
// Created by 张程易 on 30/12/2017.
//

#ifndef ELFGE_PARTICLEFACTORY_H
#define ELFGE_PARTICLEFACTORY_H

#include "GameEngine.h"
#include "ParticleBundle.h"

class ParticleFactory: public Component {
    Shader* shader;
    std::vector<ParticleBundle> bundles;
    glm::mat4 ortho;
    unsigned int fog, spot;
public:
    void start() override;
    void updateGraphics(RenderLayer renderLayer) override;
    void addExplosion();
};

#endif //ELFGE_PARTICLEFACTORY_H
