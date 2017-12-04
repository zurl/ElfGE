//
// Created by sky on 2017/12/4.
//

#ifndef ELFGE_RTTEXTURE_H
#define ELFGE_RTTEXTURE_H
#include "Common.h"
#include "Core/Utility.h"

class RTTexture {
public:
    unsigned int id,width,height;
    RTTexture(unsigned int width, unsigned height){

        glGenTextures(1, &id);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, id);

        // Give an empty image to OpenGL ( the last "0" means "empty" )
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB,GL_FLOAT, 0);

        // Poor filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    }
    GLint*  drawToPrepare(){
        GLint v[4];
        glGetIntegerv(GL_VIEWPORT,v);
        GLuint FramebufferName = 0, RenderbufferName = 0;
        glGenFramebuffers(1, &FramebufferName);
        glGenRenderbuffers(1, &RenderbufferName);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        glBindFramebuffer(GL_RENDERBUFFER, RenderbufferName);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, id, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RenderbufferName);

        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        glViewport(0,0,width,height);
        return v;
    }
    void drawToAfter(GLint * v){
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glViewport(v[0],v[1],v[2],v[3]);
    }

    void bind(GLuint unit = 0){
         glActiveTexture(GL_TEXTURE0 + unit);
         glBindTexture(GL_TEXTURE_2D, id);
    }
};
#endif
