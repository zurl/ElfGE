//
// Created by 张程易 on 23/12/2017.
//

#ifndef ELFGE_SELECTEDMATERIAL_H
#define ELFGE_SELECTEDMATERIAL_H

#include "GameEngine.h"

class SelectedMaterial: public Material {
    void use(Shader *shader) override;
};


#endif //ELFGE_SELECTEDMATERIAL_H
