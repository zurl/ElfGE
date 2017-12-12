//
// Created by 张程易 on 26/11/2017.
//

#ifndef ELFGE_SKYBOX_H
#define ELFGE_SKYBOX_H


#include <GameEngine.h>

class SkyBox: public Component{
    unsigned int cubemapTexture;
    unsigned int skyboxVAO, skyboxVBO;
    std::vector<std::string> faces;
    Shader * shader;
public:
    SkyBox(const std::string & path,const std::string & ext)
    :faces({
                Utility::RESOURCE_PREFIX + path + "right."+ext,
                Utility::RESOURCE_PREFIX + path + "left."+ext,
                Utility::RESOURCE_PREFIX + path + "top."+ext,
                Utility::RESOURCE_PREFIX + path + "bottom."+ext,
                Utility::RESOURCE_PREFIX + path + "back."+ext,
                Utility::RESOURCE_PREFIX + path + "front."+ext
        }){};
    void start() override;

    void updateGraphics(RenderLayer renderLayer) override;
};


#endif //ELFGE_SKYBOX_H
