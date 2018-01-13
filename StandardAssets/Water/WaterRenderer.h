//
// Created by sky on 2017/12/8.
//

#ifndef ELFGE_WATERRENDERER_H_H
#define ELFGE_WATERRENDERER_H_H
#include "WaterTile.h"
#include "WaterFrameBuffer.h"
#include <GameEngine.h>
#include <Meshs/PlaneMesh.h>
#include "../BoringHow/SkyBox.h"

static void dumpGLErrorLog(int l) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout<<"glError: "<<err<<" line_num:"<<l<<std::endl;
    }
}

class WaterRenderer : public Component{
    const float waveSpeed = 0.05f;
    float moveFactor = 0;
    PlaneMesh *quad;
    Shader *shader;
    WaterTile *water;
    WaterFrameBuffer *fbo;
    SkyBox *skybox;
    GLuint dudv,normalMap;
public:
    WaterRenderer() {
        shader = ShaderManager::getShader("water/water");
        quad = new PlaneMesh();
        water = new WaterTile(0,0,0);
//        skybox = new SkyBox("Textures/water/ame_darkgloom/","tga");
        skybox = new SkyBox("Textures/skybox/","jpg");
        skybox->start();
        fbo = new WaterFrameBuffer();
        dudv = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/water/DUDV.png");
        normalMap = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/water/matchingNormalMap.png");
    }

    void updateGraphics(RenderLayer r) {
        if(r != RenderLayer::WORLD) return;
        prepareRender();
//        for (WaterTile tile : water) {
        glm::mat4 model = glm::translate(glm::mat4(1),glm::vec3(
                water->getX(),water->getHeight(),water->getZ()))
                          * glm::scale(glm::mat4(1),glm::vec3(water->TILE_SIZE,1,water->TILE_SIZE));
//        glm::mat4 model = getGameObject()->getModelMatrix();
//            shader->setMat4("model",getGameObject()->getModelMatrix());
        shader->setMat4("model",model);

        quad->render(shader,RenderLayer::WORLD);
        dumpGLErrorLog(__LINE__);
        unbind();
    }

    void prepareRender(){
        shader->use();
        LightingManager::update(shader);
        shader->setMat4("view", Runtime::getCamera()->getViewMatrix());
        shader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
        shader->setInt("reflectionTexture",0);
        shader->setInt("refractionTexture",1);
        shader->setInt("dudvMap",2);
        shader->setFloat("moveFactor",moveFactor);
        shader->setVec3("cameraPosition",Runtime::getCamera()->getGameObject()->getWorldPosition());
        shader->setVec3("lightPosition",glm::vec3(100,100,100));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,fbo->getReflectionTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,fbo->getRefractionTexture());
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D,dudv);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D,normalMap);
    }

    void unbind(){
    }

    void update(){
        moveFactor += waveSpeed * Utility::deltaTime;
        moveFactor = moveFactor - floor(moveFactor);
        fbo->bindReflectionFrameBuffer();
        Camera *c = Runtime::getCamera();
        glm::vec3  position = c->getGameObject()->transform.getLocalPosition();
        float distance = 2*(c->getGameObject()->transform.getLocalPosition().y
                            -water->getHeight());
        position.z -= distance;
        glm::vec3 rotation = c->getGameObject()->transform.getLocalRotation();
        rotation.z = -1*rotation.z;
        c->getGameObject()->transform.setPosition(position);
        c->getGameObject()->transform.setRotation(rotation);

        fbo->bindReflectionFrameBuffer();
        skybox->updateGraphics(RenderLayer::WORLD);

        position.z += distance;
        rotation.z = -1*rotation.z;

        c->getGameObject()->transform.setPosition(position);
        c->getGameObject()->transform.setRotation(rotation);

        fbo->bindRefractionFrameBuffer();
        skybox->updateGraphics(RenderLayer::WORLD);
        fbo->bindRefractionFrameBuffer();

        fbo->unbindCurrentFrameBuffer();
    }

};
#endif //ELFGE_WATERRENDERER_H_H