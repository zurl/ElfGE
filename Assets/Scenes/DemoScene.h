//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEMOSCENE_H
#define ELFGE_DEMOSCENE_H


#include "../../Scene.h"
#include "../../ELFGE.h"
#include "../../Meshs/CubeMesh.h"
#include "../../DefaultMaterial.h"

class DemoScene: public Scene {

    DefaultMaterial material;

public:

    DemoScene();

    void start() override;

    void update() override;
};


#endif //ELFGE_DEMOSCENE_H
