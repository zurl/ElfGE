//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_CUBEMESH_H
#define ELFGE_CUBEMESH_H


#include "DefaultMesh.h"
#include "GameEngine.h"

class CubeMesh: public DefaultMesh {
public:
    CubeMesh();
    CubeMesh(const std::string specularName, const std::string diffuseName);
};


#endif //ELFGE_CUBEMESH_H
