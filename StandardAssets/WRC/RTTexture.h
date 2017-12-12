//
// Created by sky on 2017/12/4.
//

#ifndef ELFGE_RTTEXTURE_H
#define ELFGE_RTTEXTURE_H
#include "Common.h"
#include "Core/Utility.h"
static void dumpGLErrorLog(void) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout<<"glError: "<<err<<std::endl;
    }
}

static void dumpGLErrorLog(unsigned int l) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout<<"glError: "<<err<<"line:"<<l<<std::endl;
    }
}

class RTTexture {

    GLuint FramebufferName = 0, RenderbufferName = 0;
public:
    unsigned int id,width,height;
    RTTexture(unsigned int width, unsigned height):width(width),height(height){

        glGenFramebuffers(1, &FramebufferName);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        // create a color attachment texture

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, id, 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        dumpGLErrorLog(__LINE__);
    }
    std::vector<GLuint>  drawToPrepare(){
        GLint v[4];
        glGetIntegerv(GL_VIEWPORT,v);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        dumpGLErrorLog(__LINE__);
        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
        dumpGLErrorLog(__LINE__);
        std::vector<GLuint> vv(4);
        for(int i=0;i<4;i++) vv[i] = v[i];
        return vv;
    }
    void drawToAfter(const std::vector<GLuint> & v){
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
        dumpGLErrorLog(__LINE__);
    }

    void bind(GLuint unit = 0){
         glActiveTexture(GL_TEXTURE0 + unit);
         glBindTexture(GL_TEXTURE_2D, id);
    }
};
#endif
