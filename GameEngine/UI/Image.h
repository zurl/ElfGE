//
// Created by 张程易 on 19/11/2017.
//

#ifndef ELFGE_IMAGE_H
#define ELFGE_IMAGE_H

#include "GameEngine.h"

class Image: public Component {
    unsigned int texture;
    Shader * UIShader;
    static GLuint VAO, VBO;
    static bool isInit;
    float width, height;
    bool isCenter;
    GLfloat vertices[6][4] ={
        { -1.0f, 1.0f, 0.0f, 0.0f },
        { -1.0f, -1.0f, 0.0f, 1.0f },
        { 1.0f, -1.0f, 1.0f, 1.0f },
        { -1.0f, 1.0f, 0.0f, 0.0f },
        { 1.0f, -1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f, 0.0f }
    };
public:
    Image(unsigned int texture, float width, float height, bool isCenter = true);

    void start() override;

    void updateGraphics(RenderLayer renderLayer) override;
};


#endif //ELFGE_IMAGE_H
