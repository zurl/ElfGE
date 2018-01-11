//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_STANDARDMATERIAL_H
#define ELFGE_STANDARDMATERIAL_H
#include "GameEngine.h"

class StandardMaterial: public Material {

    static StandardMaterial instance;

public:
    void use(Shader *shader) override;

    static Material * getInstance();
};


#endif //ELFGE_STANDARDMATERIAL_H
