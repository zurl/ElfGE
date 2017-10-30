//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_POINTLIGHTING_H
#define ELFGE_POINTLIGHTING_H

#include "../../GameEngine/ELFGE.h"

class PointLighting: public Lighting{

public:

    std::string getName() override;

    void update(const std::string &prefix, Shader *shader) override;
};


#endif //ELFGE_POINTLIGHTING_H
