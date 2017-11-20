//
// Created by 张程易 on 30/10/2017.
//


#include <Graphics/GraphicsRuntime.h>
#include "Runtime.h"
#include "Input.h"
#include "Core/Scene.h"

Scene * Runtime::scene;
GraphicsRuntime Runtime::graphicsRuntime;
void Runtime::start() {
    graphicsRuntime.initialize();
    FontManager::initialize();
    Input::initialize();
    Entry::start();
    setScene(Entry::getDefaultScene());
    getScene()->start();
    double lastFrame = glfwGetTime();
    while(!glfwWindowShouldClose(Utility::window)) {

        double currentFrame = glfwGetTime();
        Utility::deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        getScene()->update();

        graphicsRuntime.update(getScene());

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
