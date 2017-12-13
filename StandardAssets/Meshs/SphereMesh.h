//
// Created by sky on 2017/12/4.
//

#ifndef ELFGE_SPHEREMESH_H
#define ELFGE_SPHEREMESH_H

#include "DefaultMesh.h"
#include "GameEngine.h"

class SphereMesh : public DefaultMesh {
public:
    SphereMesh();

    SphereMesh(const std::string specularName, const std::string diffuseName, const std::string normalName = "");
};

#endif //ELFGE_SPHEREMESH_H
