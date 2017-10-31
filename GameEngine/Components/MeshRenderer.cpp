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
        shader->use();
        shader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
        shader->setMat4("view", Runtime::getCamera()->getViewMatrix());
        LightingManager::update(shader);
        shader->setVec3("viewPos", Runtime::getCamera()->getGameObject()->transform.getPosition());
    }
    shader->setMat4("model", getGameObject()->getModelMatrix());
    material->use(shader);
    model->render(shader);
}

void MeshRenderer::start() {
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

void MeshRenderer::destroy() {

}
