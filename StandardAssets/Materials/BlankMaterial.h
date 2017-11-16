//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEFAULTMATERIAL_H
#define ELFGE_DEFAULTMATERIAL_H


#include "GameEngine.h"

class BlankMaterial: public Material {
public:
    void use(Shader *shader) override;
};


#endif //ELFGE_DEFAULTMATERIAL_H
