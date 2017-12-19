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
    glfwSetInputMode(Utility::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (Utility::window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(Utility::window);
#ifndef __linux
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
#else
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "init glad failed." << std::endl;
        exit(1);
    }
#endif
    glViewport(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(Utility::window, framebuffer_size_callback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    debugUtility.shader = ShaderManager::getShader("depth_debug");
}


void GraphicsRuntime::update(Scene *scene) {

    if (scene->getShadowMappingManager() != nullptr) {
        scene->getShadowMappingManager()->computeMapping();
        scene->updateGraphics(RenderLayer::WORLD_SHADOW);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
    scene->updateGraphics(RenderLayer::WORLD);
//    debugUtility.shader->use();
//
//    debugUtility.shader->setInt("depthMap", 8);
//    scene->getShadowMappingManager()->applyMapping(debugUtility.shader);
//    debugUtility.RenderQuad();
    //scene->updateGraphics(RenderLayer::WORLD);

    scene->updateGraphics(RenderLayer::SCREEN);
}
