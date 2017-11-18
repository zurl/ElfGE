//
// Created by 张程易 on 17/11/2017.
//

#ifndef ELFGE_DEBUGUTILITY_H
#define ELFGE_DEBUGUTILITY_H

#include "GameEngine.h"

class DebugUtility {
public:
    GLuint quadVAO, quadVBO;
    Shader * shader;
    void RenderQuad() {
        if (quadVAO == 0) {
            GLfloat quadVertices[] = {
                    // Positions        // Texture Coords
                    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
                    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
                    1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
                    1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
            };
            // Setup plane VAO
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        }
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
};


#endif //ELFGE_DEBUGUTILITY_H
