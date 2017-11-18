//
// Created by 张程易 on 17/11/2017.
//

#include "GraphicsRuntime.h"

#include "DebugUtility.h"
DebugUtility debugUtility;

void GraphicsRuntime::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    Utility::SCREEN_HEIGHT = height;
    Utility::SCREEN_WIDTH = width;
}


void GraphicsRuntime::initialize() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    Utility::window = glfwCreateWindow(Utility::SCREEN_WIDTH,
                                       Utility::SCREEN_HEIGHT,
                                       Utility::WINDOW_NAME.c_str(), NULL, NULL);
    //glfwSetInputMode(__glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (Utility::window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(Utility::window);
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    glViewport(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(Utility::window, framebuffer_size_callback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    debugUtility.shader = ShaderManager::getShader("depth_debug");
}


void GraphicsRuntime::update(Scene *scene) {


    scene->getShadowMappingManager()->computeMapping();
    scene->updateGraphics(RenderLayer::WORLD_SHADOW);

    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->updateGraphics(RenderLayer::WORLD);
//    debugUtility.shader->use();
//
//    debugUtility.shader->setInt("depthMap", 8);
//    scene->getShadowMappingManager()->applyMapping(debugUtility.shader);
//    debugUtility.RenderQuad();
    //scene->updateGraphics(RenderLayer::WORLD);

    //scene->updateGraphics(RenderLayer::SCREEN);
}
