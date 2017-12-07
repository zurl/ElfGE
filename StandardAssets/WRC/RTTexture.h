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

        glGenTextures(1, &id);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, id);


        // Poor filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Give an empty image to OpenGL ( the last "0" means "empty" )
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16, width, height, 0,GL_RGB,GL_FLOAT, 0);
        glGenFramebuffers(1, &FramebufferName);
        glGenRenderbuffers(1, &RenderbufferName);
        dumpGLErrorLog(__LINE__);
    }
    std::vector<GLuint>  drawToPrepare(){
        dumpGLErrorLog(__LINE__);
        GLint v[4];
        glGetIntegerv(GL_VIEWPORT,v);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        glBindRenderbuffer(GL_RENDERBUFFER, RenderbufferName);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
//        dumpGLErrorLog(__LINE__);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, id, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RenderbufferName);

//        dumpGLErrorLog(__LINE__);
        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
        dumpGLErrorLog(__LINE__);
        std::vector<GLuint> vv(4);
        for(int i=0;i<4;i++) vv[i] = v[i];
        return vv;
    }
    void drawToAfter(const std::vector<GLuint> & v){
        dumpGLErrorLog(__LINE__);
        glViewport(0,0,width,height);
        dumpGLErrorLog(__LINE__);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        dumpGLErrorLog(__LINE__);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glViewport(v[0],v[1],v[2],v[3]);
        dumpGLErrorLog(__LINE__);
    }

    void bind(GLuint unit = 0){
         glActiveTexture(GL_TEXTURE0 + unit);
         glBindTexture(GL_TEXTURE_2D, id);
    }
};
#endif
