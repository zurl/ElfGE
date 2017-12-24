//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_MESH_H
#define ELFGE_MESH_H

#include "Common.h"
#include "Graphics/Shader.h"
#include "Model.h"

class Mesh : public Model {
public:
    std::string getName() override {
        return "mesh";
    }
    virtual void render(Shader *shader, RenderLayer renderLayer) override = 0;
    virtual ~Mesh() {}
};


#endif //ELFGE_MESH_H
