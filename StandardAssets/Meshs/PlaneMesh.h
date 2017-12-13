//
// Created by sky on 2017/12/4.
//

#ifndef ELFGE_PLANEMESH_H
#define ELFGE_PLANEMESH_H

#include "DefaultMesh.h"
#include "GameEngine.h"

class PlaneMesh : public DefaultMesh {
public:
    PlaneMesh();

    PlaneMesh(const std::string &specularName, const std::string &diffuseName, const std::string &normalName = "");
};

#endif //ELFGE_PLANEMESH_H
