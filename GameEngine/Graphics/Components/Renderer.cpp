//
// Created by 张程易 on 29/10/2017.
//

#include <Graphics/ShaderManager.h>
#include <Config.h>
#include "Renderer.h"
#include "Core/Runtime.h"
#include "Graphics/LightingManager.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Core/Camera.h"

void Renderer::updateGraphics(RenderLayer renderLayer) {
    if (Runtime::getCamera() == nullptr) {
        throw Exception("No Camera");
    }
    if (useShadow && renderLayer == RenderLayer::WORLD_SHADOW) {
        Shader *shadowShader = Runtime::getScene()->getShadowMappingManager()->getShader();
        shadowShader->setMat4("model", getGameObject()->getModelMatrix());
        model->render(shadowShader, renderLayer);
    }
    if (renderLayer == RenderLayer::WORLD) {
        if (true||!ShaderManager::useShader(shader)) {
            shader->use();
            auto smm = Runtime::getScene()->getShadowMappingManager();
            if (smm != nullptr) smm->applyMapping(shader);
            shader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
            shader->setMat4("view", Runtime::getCamera()->getViewMatrix());
            LightingManager::update(shader);
            shader->setVec3("viewPos", Runtime::getCamera()->getGameObject()->getWorldPosition());
        }
        shader->setMat4("model", getGameObject()->getModelMatrix());
        if (material != nullptr) material->use(shader);

        if ( isSelected ) {
            glEnable(GL_STENCIL_TEST);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glClear(GL_STENCIL_BUFFER_BIT);
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
            model->render(shader, renderLayer);
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            ShaderManager::useShader(borderShader);
            borderShader->use();
            borderShader->setMat4("model", getGameObject()->getModelMatrix());
            borderShader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
            borderShader->setMat4("view", Runtime::getCamera()->getViewMatrix());
            model->render(borderShader, renderLayer);
            glDisable(GL_STENCIL_TEST);
        }
        else{
            model->render(shader, renderLayer);
        }
    }
}

void Renderer::start() {
    borderShader = ShaderManager::getShader("border");
    if (getGameObject() == nullptr) {
        throw Exception("A MeshRender Without Parents");
    }
    if (getGameObject() != nullptr) {
        model = getGameObject()->getComponent<Model>();
    }
    if (model == nullptr) {
        throw Exception("GameObject contains no Model");
    }
}

void Renderer::destroy() {

}

Renderer::Renderer(Material *material, Shader *shader, bool useShadow) : material(material), shader(shader),
                                                                         useShadow(useShadow) {}

Material *Renderer::getMaterial() const {
    return material;
}

void Renderer::setMaterial(Material *material) {
    Renderer::material = material;
}

std::string Renderer::getName() {
    return "renderer";
}

bool Renderer::getSelected() const {
    return isSelected;
}

void Renderer::setSelected(bool isSelected) {
    Renderer::isSelected = isSelected;
}
