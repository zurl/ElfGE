//
// Created by 张程易 on 17/11/2017.
//

#ifndef ELFGE_SHADOWMAPPINGMANAGER_H
#define ELFGE_SHADOWMAPPINGMANAGER_H

#include "Common.h"
#include "Shader.h"

class ShadowMappingManager {
public:
    virtual void initialize() = 0;

    virtual void computeMapping() = 0;

    virtual void applyMapping(Shader * shader) = 0;

    virtual ~ShadowMappingManager(){}
};


#endif //ELFGE_SHADOWMAPPINGMANAGER_H
