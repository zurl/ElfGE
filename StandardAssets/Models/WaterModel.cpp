//
// Created by sky on 2017/12/4.
//

#include <Meshs/CubeMesh.h>
#include "WaterModel.h"

void WaterModel::stepSimulation() {
//    Shader *s = ShaderManager::getShader("water/update");
    updateS->use();
    std::vector<GLuint> v = textureB->drawToPrepare();
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"Failed to bind fram buffer\n";
        v = textureB->drawToPrepare();
//            return std::vector<GLuint>(0);
    }
    updateS->setVec2("delta",1.0f/textureA->width,1.0f/textureA->height);
    drawPlane(textureA,updateS);
    textureB->drawToAfter(v);
    RTTexture * t = textureA;
    textureA = textureB;
    textureB = t;
}

void WaterModel::updateGraphics(RenderLayer r){
    if(r != RenderLayer::WORLD) return;


    testS->use();
    testS->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
    testS->setMat4("view", Runtime::getCamera()->getViewMatrix());
    testS->setMat4("model", getGameObject()->getModelMatrix());
    testS->setInt("texture",0);
    textureA->bind();
    wplane->render(testS,RenderLayer::WORLD);
    glm::vec4 eye;
    eye = glm::inverse(Runtime::getCamera()->getViewMatrix())*glm::vec4(0,1,0,1);
    waterS->use();
//    updateS->use();
//    waterS->setVec3("light",glm::vec3(eye));
    waterS->setVec3("light",glm::vec3(0,1,0));
    waterS->setInt("water",0);
    waterS->setInt("tiles",1);
    waterS->setInt("sky",2);
    waterS->setInt("causticTex",3);
    waterS->setVec3("eye",eye);
    waterS->setVec3("eye",glm::vec3(0,1,0));
    waterS->setVec3("sphereCenter",0.5,0.5,0.5);
    waterS->setFloat("sphereRadius",0);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, textureA->id);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tileTexture);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
    glActiveTexture(GL_TEXTURE0 + 3);
    glBindTexture(GL_TEXTURE_2D, causticTex->id);

    waterS->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
    waterS->setMat4("view", Runtime::getCamera()->getViewMatrix());
    waterS->setMat4("model", getGameObject()->getModelMatrix());
    glEnable(GL_CULL_FACE);
    wplane->render(waterS,RenderLayer::WORLD);
    glDisable(GL_CULL_FACE);
}


void WaterModel::start() {


}

void WaterModel::addDrop(float x, float y, float radius, float strength) {

    std::vector<GLuint>  v = textureB->drawToPrepare();
    dropS->use();
    dropS->setVec2("center",x,y);
    dropS->setFloat("radius",radius);
    dropS->setFloat("strength",strength);
    drawPlane(textureA,dropS);
    textureB->drawToAfter(v);
    drawPlane(textureA,dropS);
    RTTexture * t = textureA;
    textureA = textureB;
    textureB = t;
}

void WaterModel::update() {
    static int ct = 0;
    ct++;
    if(ct == 100) ct = 0;
    if(ct == 5){
        addDrop(0.1*ct,0.1*ct,0.03,0.01);
    }
        stepSimulation();
        updateNormals();
}

void WaterModel::updateNormals() {
    normalS->use();
    std::vector<GLuint>  v = textureB->drawToPrepare();
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"Failed to bind fram buffer\n";
        v = textureB->drawToPrepare();
//            return std::vector<GLuint>(0);
    }
    normalS->setVec2("delta",1.0f/textureA->width,1.0f/textureA->height);
    drawPlane(textureA,normalS);
    textureB->drawToAfter(v);
    RTTexture * t = textureA;
    textureA = textureB;
    textureB = t;
}

