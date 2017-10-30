//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_RUNTIME_H
#define ELFGE_RUNTIME_H


#include "Scene.h"
#include "Utility.h"
#include "Assets/Entry.h"

class Runtime {
    static Scene * scene;
public:

    static Scene *getScene() {
        return scene;
    }

    static void setScene(Scene *scene) {
        Runtime::scene = scene;
    }

    static Camera *getCamera(){
       return getScene()->getCamera();
    }

    static void setCamera(Camera *camera){
        getScene()->getCamera();
    }



    static void __start(){
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

            glfwSwapBuffers(Utility::window);
            glfwPollEvents();
        }
    }

};


#endif //ELFGE_RUNTIME_H
