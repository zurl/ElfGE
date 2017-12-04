//
// Created by sky on 2017/12/4.
//

#ifndef ELFGE_WATERMODEL_H
#define ELFGE_WATERMODEL_H

#include <GameEngine.h>
#include "StandardAssets.h"

class WaterModel : Model{
    GLuint skyTexture,tileTexture;
    RTTexture *textureA,*textureB,*causticTex;
    PlaneMesh *cplane,*wplane;
    Shader *waterS;
    std::vector<std::string> faces;
    std::string tile;
    void stepSimulation();
    void updateNormals();
    void drawPlane(RTTexture *t, Shader *s){
        t->bind();
        cplane->render(s,RenderLayer::WORLD);
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
            Utility::RESOURCE_PREFIX + path + "tile.jpg"
    ){};
    void addDrop(float x, float y, float radius, float strength);
    void start () override;
    void update () override;
    void render (Shader *shader, RenderLayer renderLayer) override;
};
#endif //ELFGE_WATERMODEL_H
