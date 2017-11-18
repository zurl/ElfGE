//
// Created by 张程易 on 17/11/2017.
//

#ifndef ELFGE_DIRECTIONALSHADOWMAPPINGMANAGER_H
#define ELFGE_DIRECTIONALSHADOWMAPPINGMANAGER_H

#include "GameEngine.h"

class DirectionalShadowMappingManager: public ShadowMappingManager {

    unsigned int framebuffer;
    unsigned int textureColorbuffer;
    unsigned int rbo;

    int resolution;
    glm::vec3 position;
    Shader * shader;

    glm::mat4 projection, view;
public:
    DirectionalShadowMappingManager(const glm::vec3 &position, int resolution = 1024);

    void initialize();

    void computeMapping();

    void applyMapping(Shader * shader);

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    virtual ~DirectionalShadowMappingManager();

};


#endif //ELFGE_DIRECTIONALSHADOWMAPPINGMANAGER_H
