//
// Created by 张程易 on 31/10/2017.
//

#include "StandardMaterial.h"

void StandardMaterial::use(Shader *shader) {
    shader->setFloat("material.shininess", 32.0f);
}
