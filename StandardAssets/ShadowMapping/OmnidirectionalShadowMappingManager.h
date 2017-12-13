//
// Created by 张程易 on 18/11/2017.
//

#ifndef ELFGE_OMNIDIRECTIONALSHADOWMAPPINGMANAGER_H
#define ELFGE_OMNIDIRECTIONALSHADOWMAPPINGMANAGER_H

#include "GameEngine.h"
#include "../Lightings/PointLighting.h"

class OmnidirectionalShadowMappingManager : public ShadowMappingManager {
    PointLighting *pointLighting;
    int resolution;
    GLuint depthMapFBO;
    GLuint depthCubemap;
    Shader *shader;
public:
    OmnidirectionalShadowMappingManager(PointLighting *pointLighting, int resolution = 1024);

    void initialize() override;

    void computeMapping() override;

    void applyMapping(Shader *shader) override;

    Shader *getShader() override;
};


#endif //ELFGE_OMNIDIRECTIONALSHADOWMAPPINGMANAGER_H
