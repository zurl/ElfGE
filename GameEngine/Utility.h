//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_UTILITY_H
#define ELFGE_UTILITY_H

#include "Common.h"

class Utility {
public:

    static GLFWwindow* window;

    static std::string WINDOW_NAME;
    static std::string ASSETS_PREFIX;

    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    static double deltaTime;

    static const char * getTextFromFile(const char * filePath){
        FILE * fp = fopen(filePath, "r");
        if( fp == nullptr ) return nullptr;
        fseek(fp, 0L, SEEK_END);
        long flen = ftell(fp);
        char * result = (char *)malloc((size_t)flen);
        fseek(fp, 0L, SEEK_SET);
        char * now = result; int c;
        while((c = fgetc(fp))!= EOF) *now++ = (char) c;
        *now = 0;
        return result;
    }



    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        SCREEN_HEIGHT = height;
        SCREEN_WIDTH = width;
    }


    static int __initialOpenGL(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME.c_str(), NULL, NULL);
        //glfwSetInputMode(__glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        GLenum err = glewInit();
        if(err != GLEW_OK) {
            std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
            exit(1);
        }
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        return 0;
    }

};


#endif //ELFGE_UTILITY_H
