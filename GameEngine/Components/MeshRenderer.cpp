//
// Created by 张程易 on 29/10/2017.
//

#include "MeshRenderer.h"
#include "../Core/Runtime.h"


MeshRenderer::MeshRenderer(Material *material, Shader *shader) : material(material), shader(shader) {}

void MeshRenderer::update() {
    shader->__use();
    if( Runtime::getCamera() == nullptr ){
        throw Exception("No Camera");
    }
    shader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
    shader->setMat4("view", Runtime::getCamera()->getViewMatrix());
    shader->setMat4("model", getParent()->getModelMatrix());
    auto proj = Runtime::getCamera()->getProjectionMatrix();
    auto view = Runtime::getCamera()->getViewMatrix();
    auto models = getParent()->getModelMatrix();
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
