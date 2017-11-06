//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_MESHRENDER_H
#define ELFGE_MESHRENDER_H


#include "../Core/Component.h"
#include "../Shader/Material.h"
#include "../Shader/Shader.h"
#include "Model.h"

class Renderer: public Component {
    Material * material;
    Shader * shader;
    Model * model;
public:
    Renderer(Material *material, Shader *shader);
    void start() override;
    void update() override;
    void destroy() override;
};


#endif //ELFGE_MESHRENDER_H
