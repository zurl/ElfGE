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

    GameObject * cube1, * cube2, * cube3;

    DemoScene(){}

    void start() override {

        ShaderManager::loadShader("light", "light", "light");

        auto light = Prefabs::pointLight(this, glm::vec3(0,0,0));

        auto camera = Prefabs::camera(this);

        cube1 = Prefabs::cube(this, glm::vec3(1,1,1));
        cube2 = Prefabs::cube(this, glm::vec3(1,1,3));
        cube3 = Prefabs::cube(this, glm::vec3(1,3,1));

        cube2->setParent(cube1);

        Scene::start();
    }

    void update() override {
        cube1->transform.translate(glm::vec3(0, 0, 0.01));
        cube2->transform.rotate(Transform::up, 0.01);
        cube3->transform.setScale(cube3->transform.getScale() * 0.999f);
        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
