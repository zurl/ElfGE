//
// Created by 张程易 on 01/11/2017.
//

#ifndef ELFGE_CANVAS_H
#define ELFGE_CANVAS_H

#include "GameEngine.h"

class Canvas: public Component {

    int height, width;
    glm::mat4 projection;
    Shader * UIShader;

public:
    void start() override;

    void update() override;

    void destroy() override;

    void updateGraphics(RenderLayer renderLayer) override;

};


#endif //ELFGE_CANVAS_H
