//
// Created by 张程易 on 19/11/2017.
//

#include "Image.h"
GLuint Image::VAO, Image::VBO;
bool Image::isInit = false;

FontFace * ff;

void Image::start() {
    UIShader = ShaderManager::getShader("UI");
    if( !isInit ){
        isInit = true;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    ff = FontManager::loadFont("Arial");
}

void Image::updateGraphics(RenderLayer renderLayer) {
    if( renderLayer == RenderLayer::SCREEN){
        UIShader->setMat4("model", getGameObject()->getModelMatrix());
        UIShader->setVec3("color", glm::vec3(1.0f));
        UIShader->setInt("text", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

Image::Image(unsigned int texture, float width, float height, bool isCenter) :
        texture(texture), width(width), height(height), isCenter(isCenter) {
    for(int i = 0; i < 6; i++){
        if(!isCenter){
            vertices[i][0] *= width;
            vertices[i][1] *= height;
            if(vertices[i][0] < 0) vertices[i][0] = 0;
            if(vertices[i][1] < 0) vertices[i][1] = 0;
        }
        else{
            vertices[i][0] *= width / 2;
            vertices[i][1] *= height / 2;
        }
    }
}
