//
// Created by 张程易 on 29/10/2017.
//

#include "Renderer.h"
#include "Core/Runtime.h"
#include "Graphics/LightingManager.h"

void Renderer::updateGraphics(RenderLayer renderLayer) {
    if( Runtime::getCamera() == nullptr ){
        throw Exception("No Camera");
    }
    if( useShadow && renderLayer == RenderLayer::WORLD_SHADOW){
        shader->setMat4("model", getGameObject()->getModelMatrix());
        model->render(shader);
    }
    if( renderLayer == RenderLayer::WORLD ){
        if(!ShaderManager::useShader(shader)){
            shader->use();
            auto smm = Runtime::getScene()->getShadowMappingManager();
            if( smm != nullptr ) smm->applyMapping(shader);
            shader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
            shader->setMat4("view", Runtime::getCamera()->getViewMatrix());
            LightingManager::update(shader);
            shader->setVec3("viewPos", Runtime::getCamera()->getGameObject()->transform.getPosition());
        }
        shader->setMat4("model", getGameObject()->getModelMatrix());
        if( material != nullptr) material->use(shader);
        model->render(shader);
    }
}

void Renderer::start() {
    if( getGameObject() == nullptr){
        throw Exception("A MeshRender Without Parents");
    }
    if( getGameObject() != nullptr ){
        model = getGameObject()->getComponent<Model>();
    }
    if( model == nullptr ){
        throw Exception("GameObject contains no Model");
    }
}

void Renderer::destroy() {

}

Renderer::Renderer(Material *material, Shader *shader, bool useShadow) : material(material), shader(shader),
                                                                         useShadow(useShadow) {}
