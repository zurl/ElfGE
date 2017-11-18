//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEMOSCENE_H
#define ELFGE_DEMOSCENE_H


#include "GameEngine.h"
#include "StandardAssets.h"
#include "UI/UI.h"
#include "../Prefabs.h"
#include "../FuckScript.h"

class DemoScene: public Scene {

public:

    GameObject * cube1, * cube2, * cube3, * cube4, * cube5;

    DemoScene(){}

    StandardMaterial material;

    Text * text;

    void start() override {

        setShadowMappingManager(new DirectionalShadowMappingManager(glm::vec3(0, 0, 60)));
        getShadowMappingManager()->initialize();
        getShadowMappingManager()->setPosition(glm::vec3(-2, 2, 0));

        auto cube1 = Prefabs::cube(this, glm::vec3(0.0f, 1.5f, 0.0));
        auto cube2 = Prefabs::cube(this, glm::vec3(2.0f, 0.0f, 1.0));
        auto cube3 = Prefabs::cube(this, glm::vec3(-1.0f, 0.0f, 2.0));

        auto plane = Prefabs::cube(this, glm::vec3(0.0f, 0.0f, 0.0f));
        plane->transform.setScale(glm::vec3(15.0f, 0.05f, 15.0f));
//        auto arialFont = FontManager::loadFont("Arial");

        auto light = Prefabs::dirLight(this, glm::vec3(0, 0, 60));
//
        auto camera = Prefabs::camera(this);
//
        camera->transform.setPosition(glm::vec3(-2, 2, 0));
//
//        cube1 = Prefabs::cube(this, glm::vec3(1,1,1));
//        cube2 = Prefabs::cube(this, glm::vec3(1,1,3));
//
//        cube4 = Prefabs::cube(this, glm::vec3(1,1,7));
//        cube5 = Prefabs::cube(this, glm::vec3(1,1,10));
//
//        cube1->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.5, false);
//        cube2->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.5, false);
//
//        cube1->createComponent<AABBCollider>(false);
//        cube2->createComponent<AABBCollider>(false);
//
//        cube4->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.5, false);
//        cube5->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.5, false);
//
//        cube4->createComponent<AABBCollider>(false);
//        cube5->createComponent<AABBCollider>(false);
//
//        cube2->createComponent<FuckScript>();
//
//
//        auto plane = Prefabs::cube(this, glm::vec3(0 ,0, 0));

//
//
//        auto nano = createGameObject()
//                ->createComponent<DefaultModel>(Utility::RESOURCE_PREFIX + "nanosuit/nanosuit.obj")
//                ->createComponent<Renderer>(&material, ShaderManager::getShader("light"))
//                //->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0.01f), glm::vec3(0, 0, 0), 0.5, false)
//                ->createComponent<AABBCollider>(false);
//
//        nano->transform.setScale(nano->transform.getScale() * 0.05f);
//        nano->transform.setPosition(glm::vec3(1,1,-5));
//
//
//        auto canvas = createGameObject()->createComponent<Canvas>();
//
//        auto text1 = createGameObject()->createComponent<Text>("hello world!", arialFont);
//
//        text1->setParent(canvas);
//        text1->transform.translate(glm::vec3(20, 20, 0));
//        text  = text1->getComponent<Text>();
//        text->setFontColor(glm::vec3(0.5f, 0.5f, 0.0f));

        Scene::start();
    }

    float dir = 0.01f;
    int cnt = 0;
    float dt;

    std::string itos(int i){
        std::ostringstream iss;
        iss<<i;
        return iss.str();
    }

    void update() override {
//        cnt ++;
//        dt += Utility::deltaTime;
//        if(dt >= 1.0f){
//            dt = 0;
//            text->setText("FPS:" + itos(cnt));
//            cnt = 0;
//        }
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
