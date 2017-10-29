//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_MESHRENDER_H
#define ELFGE_MESHRENDER_H


#include "Component.h"
#include "Material.h"
#include "Shader.h"
#include "Model.h"

class MeshRenderer: public Component {
    Material * material;
    Shader * shader;
    Model * model;
public:
    MeshRenderer(Material *material, Shader *shader);
    void update() override;
};


#endif //ELFGE_MESHRENDER_H
