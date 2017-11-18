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
    DirectionalShadowMappingManager(DirectLighting * directLighting, int resolution = 1024);

    void initialize();

    void computeMapping();

    void applyMapping(Shader * shader);

    virtual ~DirectionalShadowMappingManager();

};


#endif //ELFGE_DIRECTIONALSHADOWMAPPINGMANAGER_H
