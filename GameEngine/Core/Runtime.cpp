//
// Created by 张程易 on 30/10/2017.
//

#include "Runtime.h"

Scene * Runtime::scene;

void Runtime::start() {
    Utility::__initialOpenGL();
    Input::initialize();
    Entry::start();
    setScene(Entry::getDefaultScene());
    getScene()->start();
    double lastFrame = glfwGetTime();
    while(!glfwWindowShouldClose(Utility::window)) {

        double currentFrame = glfwGetTime();
        Utility::deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        getScene()->update();   // EntryPoint
        //UI::drawUI();

        glfwSwapBuffers(Utility::window);
        glfwPollEvents();
    }
}

Scene *Runtime::getScene() {
    return scene;
}

void Runtime::setScene(Scene *scene) {
    if(Runtime::scene != nullptr){
        Runtime::scene->destroy();
        delete Runtime::scene;
    }
    Runtime::scene = scene;
}

void Runtime::setCamera(Camera *camera) {
    getScene()->getCamera();
}

Camera *Runtime::getCamera() {
    return getScene()->getCamera();
}
