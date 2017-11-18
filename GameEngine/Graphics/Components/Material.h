//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_MATERIAL_H
#define ELFGE_MATERIAL_H


#include "Graphics/Shader.h"

class Material {
public:
    virtual void use(Shader * shader) = 0;
};


#endif //ELFGE_MATERIAL_H
