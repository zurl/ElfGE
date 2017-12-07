//
// Created by sky on 2017/12/4.
//

#ifndef ELFGE_WATERMODEL_H
#define ELFGE_WATERMODEL_H

#include <GameEngine.h>
#include <WRC/RTTexture.h>
#include "DefaultModel.h"
#include "../Meshs/PlaneMesh.h"

class WaterModel : public Component{
    GLuint skyTexture,tileTexture;
    RTTexture *textureA,*textureB,*causticTex;
    PlaneMesh *cplane,*wplane;
    Shader *waterS,*updateS,*dropS,*testS,*normalS;
    std::vector<std::string> faces;
    std::string tile;
    void stepSimulation();
    void updateNormals();
    void drawPlane(RTTexture *t, Shader *s){
        dumpGLErrorLog(__LINE__);
        s->setInt("texture",0);
        dumpGLErrorLog(__LINE__);
        t->bind();
        dumpGLErrorLog(__LINE__);
        cplane->render(s,RenderLayer::WORLD);
        dumpGLErrorLog(__LINE__);
    }
public:
    WaterModel(const std::string &path):
            faces({
            Utility::RESOURCE_PREFIX + path + "right.jpg",
            Utility::RESOURCE_PREFIX + path + "left.jpg",
            Utility::RESOURCE_PREFIX + path + "top.jpg",
            Utility::RESOURCE_PREFIX + path + "top.jpg",
            Utility::RESOURCE_PREFIX + path + "back.jpg",
            Utility::RESOURCE_PREFIX + path + "front.jpg"
                  }),
            tile(
            Utility::RESOURCE_PREFIX + path + "tiles.jpg"
    ){
        waterS = ShaderManager::getShader("water/water");
        updateS = ShaderManager::getShader("water/update");
        dropS = ShaderManager::getShader("water/drop");
        testS = ShaderManager::getShader("water/test");
        normalS = ShaderManager::getShader("water/normal");
//        waterS = ShaderManager::getShader("simple");
        skyTexture = TextureManager::loadTexture3D(faces);
        tileTexture = TextureManager::loadTexture2D(tile);
        cplane = new PlaneMesh();
        wplane = new PlaneMesh();
        textureA = new RTTexture(256,256);
        textureB = new RTTexture(256,256);
        causticTex = new RTTexture(1024,1024);
        dumpGLErrorLog(__LINE__);
    };
    void addDrop(float x, float y, float radius, float strength);
    void start () override;
    void update () override;
    void updateGraphics (RenderLayer r) override;
};
#endif //ELFGE_WATERMODEL_H
