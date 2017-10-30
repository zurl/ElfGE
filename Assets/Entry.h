//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_ENTRY_H
#define ELFGE_ENTRY_H


#include "../ELFGE.h"
#include "Scenes/DemoScene.h"

class Entry {

public:

    static void start(){
        // TODO:: Write the Global Bootstrap Code here
        ShaderManager::loadShader("simple", "simple", "simple");
    }

    static Scene * getDefaultScene(){
        // TODO:: Return your Default Scene
        return new DemoScene();
    }

};


#endif //ELFGE_ENTRY_H
