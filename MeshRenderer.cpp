//
// Created by 张程易 on 29/10/2017.
//

#include "MeshRenderer.h"
#include "Runtime.h"

MeshRenderer::MeshRenderer(Material *material, Shader *shader) : material(material), shader(shader) {}

void MeshRenderer::update() {
    if( model == nullptr ){
        if( getParent() != nullptr ){
            model = getParent()->getComponent<Model>();
        }
        if( model == nullptr ){
            throw Exception("GameObject contains no Model");
        }
    }
    shader->__use();
    shader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
    shader->setMat4("view", Runtime::getCamera()->getViewMatrix());
    shader->setMat4("model", getParent()->getModelMatrix());
    material->__use(shader);
    model->__render(shader);
}
