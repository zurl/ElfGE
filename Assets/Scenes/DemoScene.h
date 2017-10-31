//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEMOSCENE_H
#define ELFGE_DEMOSCENE_H


#include "../../GameEngine/GameEngine.h"
#include "../../StandardAssets/StandardAssets.h"
#include "../Prefabs.h"
#include "../FuckScript.h"

class DemoScene: public Scene {

public:

    GameObject * cube1, * cube2, * cube3, * cube4, * cube5;

    DemoScene(){}

    StandardMaterial material;
    void start() override {

        ShaderManager::loadShader("light", "light", "light");

        auto light = Prefabs::pointLight(this, glm::vec3(0,0,0));

        auto camera = Prefabs::camera(this);

        cube1 = Prefabs::cube(this, glm::vec3(1,1,1));
        cube2 = Prefabs::cube(this, glm::vec3(1,1,3));

        cube4 = Prefabs::cube(this, glm::vec3(1,1,7));
        cube5 = Prefabs::cube(this, glm::vec3(1,1,10));

        cube1->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.5, false);
        cube2->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.5, false);

        cube1->createComponent<AABBCollider>(false);
        cube2->createComponent<AABBCollider>(false);

        cube4->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.5, false);
        cube5->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.5, false);

        cube4->createComponent<AABBCollider>(false);
        cube5->createComponent<AABBCollider>(false);

        cube2->createComponent<FuckScript>();


        auto nano = createGameObject()
        ->createComponent<DefaultModel>(Utility::ASSETS_PREFIX + "nanosuit/nanosuit.obj")
        ->createComponent<MeshRenderer>(&material, ShaderManager::getShader("light"))
        ->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0.01f), glm::vec3(0, 0, 0), 0.5, false)
        ->createComponent<AABBCollider>(false);

        nano->transform.setScale(nano->transform.getScale() * 0.05f);
        nano->transform.setPosition(glm::vec3(1,1,-5));


        Scene::start();
    }

    float dir = 0.01f;
    void update() override {
//        if(cube1->transform.getPosition().z > 5){
//            dir = -0.01f;
//        }
//        if(cube1->transform.getPosition().z < -5){
//            dir = 0.01f;
//        }
//        cube1->transform.translate(glm::vec3(0, 0, dir));
//        //cube1->transform.rotate(Transform::up, 0.01);
        //cube1->transform.rotate(Transform::forward, 0.01);
//        cube2->transform.rotate(Transform::up, 0.01);
//        cube3->transform.setScale(cube3->transform.getScale() * 0.999f);

        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
