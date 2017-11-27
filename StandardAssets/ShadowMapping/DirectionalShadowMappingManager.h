//
// Created by 张程易 on 17/11/2017.
//

#ifndef ELFGE_DIRECTIONALSHADOWMAPPINGMANAGER_H
#define ELFGE_DIRECTIONALSHADOWMAPPINGMANAGER_H

#include "GameEngine.h"
#include "../Lightings/DirectLighting.h"

class DirectionalShadowMappingManager: public ShadowMappingManager {

    unsigned int framebuffer;
    unsigned int textureColorbuffer;
    int resolution;
    DirectLighting * directLighting;
    Shader * shader;
    glm::mat4 projection, view;
public:
    DirectionalShadowMappingManager(DirectLighting * directLighting, int resolution = 512);

    void initialize() override ;

    void computeMapping() override ;

    void applyMapping(Shader * shader) override ;

    virtual ~DirectionalShadowMappingManager();

    Shader *getShader() override;

};


#endif //ELFGE_DIRECTIONALSHADOWMAPPINGMANAGER_H
