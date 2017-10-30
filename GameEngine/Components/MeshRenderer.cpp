//
// Created by 张程易 on 29/10/2017.
//

#include "MeshRenderer.h"
#include "../Core/Runtime.h"
#include "../Shader/LightingManager.h"


MeshRenderer::MeshRenderer(Material *material, Shader *shader) : material(material), shader(shader) {}

void MeshRenderer::update() {
    if( Runtime::getCamera() == nullptr ){
        throw Exception("No Camera");
    }
    if(!ShaderManager::useShader(shader)){
        shader->__use();
        shader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
        shader->setMat4("view", Runtime::getCamera()->getViewMatrix());
        LightingManager::update(shader);
    }
    shader->setMat4("model", getParent()->getModelMatrix());
    material->__use(shader);
    model->__render(shader);
}

void MeshRenderer::start() {
    if( getParent() == nullptr){
        throw Exception("A MeshRender Without Parents");
    }
    if( getParent() != nullptr ){
        model = getParent()->getComponent<Model>();
    }
    if( model == nullptr ){
        throw Exception("GameObject contains no Model");
    }
}

void MeshRenderer::destroy() {

}
