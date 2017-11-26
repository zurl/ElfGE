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

using namespace Prefabs;

class DemoScene: public Scene {

public:

    GameObject * cube1, * cube2, * cube3, * cube4, * cube5, * light;

    DemoScene(){}

    StandardMaterial material;

    Text * text;


    void start() override {

        //light = Prefabs::dirLight(this, glm::vec3(0, 0, 60));
        //light->transform.translate(-light->transform.getUp() * 3.0f);
        //light->transform.translate(-light->transform.getForward() * 5.0f);
        //setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        //getShadowMappingManager()->initialize();

        light = set<DirLight>(glm::vec3(0, 0, 60));
        light->transform.translate(-light->transform.getUp() * 10.0f);
        light->transform.translate(-light->transform.getForward() * 10.0f);
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();
        auto terrain = set<DemoTerrain>();
        auto light2 = set<PointLight>(glm::vec3(0, 0, 0));
        auto l2p = light2->getComponent<PointLighting>();
        l2p->ambient = glm::vec3(0.5f, 0.5f, 0.5f);


        auto cube1 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
        auto cube2 = set<Cube>(glm::vec3(2.0f, 3.0f, 1.0));
        auto cube3 = set<Cube>(glm::vec3(-1.0f, 3.0f, 2.0));

        auto plane = set<Cube>(glm::vec3(0.0f, 0.0f, 0.0f));
        plane->transform.setScale(glm::vec3(55.0f, 0.05f, 55.0f));

        auto arialFont = FontManager::loadFont("Arial");

        auto camera = set<Prefabs::Camera>();

        camera->transform.setPosition(glm::vec3(-2, 2, 0));

        cube4 = set<Cube>(glm::vec3(1,1,7));
        cube5 = set<Cube>(glm::vec3(1,1,10));

        camera->createComponent<FuckScript>();

        auto canvas = createGameObject()->createComponent<Canvas>();

        auto text1 = createGameObject()->createComponent<Text>("hello world!", arialFont);

        text1->setParent(canvas);
        text1->transform.translate(glm::vec3(20, 20, 0));
        text  = text1->getComponent<Text>();
        text->setFontColor(glm::vec3(0.5f, 0.5f, 0.0f));

        auto image1 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture(
                        Utility::RESOURCE_PREFIX + "Textures/cube_diffuse.png"
                ), 200.0f, 100.0f);
        image1->setParent(canvas);
        image1->transform.translate(glm::vec3(50, 50, 0));

        Scene::start();
    }

    std::string itos(int i){
        std::ostringstream iss;
        iss<<i;
        return iss.str();
    }

    void update() override {
        cnt ++;
        dt += Utility::deltaTime;
        if(dt >= 1.0f){
            dt = 0;
            text->setText("FPS:" + itos(cnt));
            cnt = 0;
        }
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
