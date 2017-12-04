//
// Created by sky on 2017/12/4.
//

#include "WaterModel.h"

void WaterModel::stepSimulation() {
    GLint  *v = textureB->drawToPrepare();
    Shader *s = ShaderManager::getShader("water/update");
    s->setVec2("delta",1/textureA->width,1/textureA->height);
    drawPlane(textureA,s);
    textureB->drawToAfter(v);
    std::swap(textureA,textureB);
}

void WaterModel::render(Shader *shader, RenderLayer renderLayer) {
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, textureA->id);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tileTexture);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glActiveTexture(GL_TEXTURE0 + 3);
    glBindTexture(GL_TEXTURE_2D, causticTex->id);
    glEnable(GL_CULL_FACE);
    wplane->render(waterS,RenderLayer::WORLD);
    glDisable(GL_CULL_FACE);
}


void WaterModel::start() {
    skyTexture = TextureManager::loadTexture3D(faces);
    tileTexture = TextureManager::loadTexture2D(tile);
    cplane = new PlaneMesh();
    wplane = new PlaneMesh();
    textureA = new RTTexture(256,256);
    textureB = new RTTexture(256,256);
    causticTex = new RTTexture(1024,1024);
    waterS = ShaderManager::getShader("water/water");
    waterS->setVec3("water",0,1,0);
    waterS->setInt("water",0);
    waterS->setInt("tiles",1);
    waterS->setInt("sky",2);
    waterS->setInt("causticTex",3);
    waterS->setVec3("eye",0,1,0);
    waterS->setVec3("sphereCenter",0,0,0);
    waterS->setFloat("causticTex",0);
}

void WaterModel::addDrop(float x, float y, float radius, float strength) {
    GLint  *v = textureB->drawToPrepare();
    Shader *s = ShaderManager::getShader("water/update");
    s->setVec2("center",x,y);
    s->setFloat("radius",radius);
    s->setFloat("strength",strength);
    drawPlane(textureA,s);
    textureB->drawToAfter(v);
    std::swap(textureA,textureB);
}

void WaterModel::update() {
    Component::update();
    stepSimulation();
    updateNormals();
}

void WaterModel::updateNormals() {
    GLint  *v = textureB->drawToPrepare();
    Shader *s = ShaderManager::getShader("water/normal");
    s->setVec2("delta",1/textureA->width,1/textureA->height);
    drawPlane(textureA,s);
    textureB->drawToAfter(v);
    std::swap(textureA,textureB);
}
