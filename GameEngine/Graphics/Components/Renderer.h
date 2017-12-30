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
    Shader *shader, *borderShader;
    Model *model;
    bool useShadow;
    bool isSelected = false;
public:
    Renderer(Material *material, Shader *shader, bool useShadow = true);

    std::string getName() override;

    void start() override;

    void updateGraphics(RenderLayer renderLayer) override;

    void destroy() override;

    Material *getMaterial() const;

    void setMaterial(Material *material);

    bool getSelected() const;

    void setSelected(bool isSelected);
};


#endif //ELFGE_MESHRENDER_H
