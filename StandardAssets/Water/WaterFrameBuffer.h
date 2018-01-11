//
// Created by sky on 2017/12/8.
//

#ifndef ELFGE_WATERFRAMEBUFFER_H
#define ELFGE_WATERFRAMEBUFFER_H
#include <GameEngine.h>
class WaterFrameBuffer {

    const  GLuint REFLECTION_WIDTH = 320;
    const  GLuint REFLECTION_HEIGHT = 180;

    const  GLuint REFRACTION_WIDTH = 1280;
    const  GLuint REFRACTION_HEIGHT = 720;

    GLuint reflectionFrameBuffer;
    GLuint reflectionTexture;
    GLuint reflectionDepthBuffer;

    GLuint refractionFrameBuffer;
    GLuint refractionTexture;
    GLuint refractionDepthTexture;

public:
    WaterFrameBuffer() {//call when loading the game
        initialiseReflectionFrameBuffer();
        initialiseRefractionFrameBuffer();
    }

    void cleanUp() {//call when closing the game
        glDeleteFramebuffers(1,&reflectionFrameBuffer);
        glDeleteTextures(1,&reflectionTexture);
        glDeleteRenderbuffers(1,&reflectionDepthBuffer);
        glDeleteFramebuffers(1,&refractionFrameBuffer);
        glDeleteTextures(1,&refractionTexture);
        glDeleteTextures(1,&refractionDepthTexture);
    }

    void bindReflectionFrameBuffer() {//call before rendering to this FBO
        bindFrameBuffer(reflectionFrameBuffer,REFLECTION_WIDTH,REFLECTION_HEIGHT);
    }

    void bindRefractionFrameBuffer() {//call before rendering to this FBO
        bindFrameBuffer(refractionFrameBuffer,REFRACTION_WIDTH,REFRACTION_HEIGHT);
    }

    void unbindCurrentFrameBuffer() {//call to switch to default frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
    }

    GLuint getReflectionTexture() {//get the resulting texture
        return reflectionTexture;
    }

    GLuint getRefractionTexture() {//get the resulting texture
        return refractionTexture;
    }

    GLuint getRefractionDepthTexture(){//get the resulting depth texture
        return refractionDepthTexture;
    }

    void initialiseReflectionFrameBuffer() {
        reflectionFrameBuffer = createFrameBuffer();
        reflectionTexture = createTextureAttachment(REFLECTION_WIDTH,REFLECTION_HEIGHT);
        reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH,REFLECTION_HEIGHT);
        unbindCurrentFrameBuffer();
    }

    void initialiseRefractionFrameBuffer() {
        refractionFrameBuffer = createFrameBuffer();
        refractionTexture = createTextureAttachment(REFRACTION_WIDTH,REFRACTION_HEIGHT);
        refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH,REFRACTION_HEIGHT);
        unbindCurrentFrameBuffer();
    }

    void bindFrameBuffer(GLuint frameBuffer, GLuint width, GLuint height){
        glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
    }

    GLuint createFrameBuffer() {
        GLuint frameBuffer;
        glGenFramebuffers(1,&frameBuffer);
        //generate name for frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        //create the framebuffer
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        //indicate that we will always render to color attachment 0
        return frameBuffer;
    }

    GLuint createTextureAttachment( GLuint width, GLuint height) {
        GLuint texture;
        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                     0, GL_RGB, GL_UNSIGNED_BYTE,  0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                             texture, 0);
        return texture;
    }

    GLuint createDepthTextureAttachment(GLuint width, GLuint height){
        GLuint texture;
        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
                     0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                             texture, 0);
        return texture;
    }

    GLuint createDepthBufferAttachment(GLuint width, GLuint height) {
        GLuint depthBuffer;
        glGenRenderbuffers(1,&depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,
                              height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER, depthBuffer);
        return depthBuffer;
    }

};

#endif //ELFGE_WATERFRAMEBUFFER_H