//
// Created by 张程易 on 23/12/2017.
//

#include "SelectedMaterial.h"

void SelectedMaterial::use(Shader *shader) {
    //shader->setFloat("material.shininess", 200.0f);
    shader->setFloat("density", 100);
}
