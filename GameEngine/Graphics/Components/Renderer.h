//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_MESHRENDER_H
#define ELFGE_MESHRENDER_H


#include "Core/Component.h"
#include "Graphics/Components/Material.h"
#include "Graphics/Shader.h"
#include "Graphics/Components/Model.h"

class Renderer : public Component {
    Material *material;
    Shader *shader;
    Model *model;
    bool useShadow;
public:
    Renderer(Material *material, Shader *shader, bool useShadow = true);

    void start() override;

    void updateGraphics(RenderLayer renderLayer) override;

    void destroy() override;

    Material *getMaterial() const;

    void setMaterial(Material *material);
};


#endif //ELFGE_MESHRENDER_H
