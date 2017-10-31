//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEMOSCENE_H
#define ELFGE_DEMOSCENE_H


#include "../../GameEngine/GameEngine.h"
#include "../../StandardAssets/StandardAssets.h"
#include "../Prefabs.h"


class DemoScene: public Scene {

public:

    DemoScene(){}

    void start() override {

        ShaderManager::loadShader("light", "light", "light");

        auto camera = Prefabs::camera(this);

        auto cube1 = Prefabs::cube(this, glm::vec3(1,1,1));
        auto cube2 = Prefabs::cube(this, glm::vec3(1,1,3));
        auto cube3 = Prefabs::cube(this, glm::vec3(1,3,1));

        Scene::start();
    }

    void update() override {
        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
