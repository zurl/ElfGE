//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_RUNTIME_H
#define ELFGE_RUNTIME_H


#include "Scene.h"
#include "Utility.h"

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
    }

    static void __runRenderLoop(){

    }

};


#endif //ELFGE_RUNTIME_H
