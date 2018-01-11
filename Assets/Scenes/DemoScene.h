//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEMOSCENE_H
#define ELFGE_DEMOSCENE_H

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_image.h"
#include "GameEngine.h"
#include "StandardAssets.h"
#include "UI/UI.h"
#include "../Prefabs.h"
#include "../Prefab/PlainText.h"
#include "../Scripts/DeveloperScript.h"
#include "../Scripts/FuckScript.h"
#include "../LJK/AnimationCond.h"
#include "../Game/Human.h"
#include "../Prefab/BasicObject.h"
#include "../Game/Land.h"
#include "../LJK/EnemyCond.h"
#include "../Game/UIManager.h"
#include "../Scripts/ModeSwitch.h"

using namespace Prefabs;

class DemoScene : public Scene {

public:

    GameObject  *ib, *dt1, *human, *realhuman, *camera,*house, *door,*cube1, *cube2, *cube3, *cube4, *cube5, *light, *foller;

    DemoScene() {}


    UIManager ui;

    void start() override {
        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/skybox/", "jpg");

        light = set<DirLight>(glm::vec3(0, 0, 60));
        light->transform.setPosition(glm::vec3(0, 15.0f, 0));
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();

        auto terrain = set<Land>();

        auto human = set<Human>(
                Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/human.dae",
                terrain->getComponent<Terrain>()
        );


        human->getComponent<AnimationCond>()->play(0);

        ui.instantiate(this);

        camera = createGameObject()
                ->createComponent<ThirdPlayerCamera>(human->getParent(), ui.getAIMScreen()->getGameObject());
        setCamera(camera->getComponent<ThirdPlayerCamera>());
        camera->setParent(human->getParent());


        auto shit = createGameObject()
        ->createComponent<DeveloperScript>(&ui, human->getParent(), light);

        auto ModeSwitcher = createGameObject()
        ->createComponent<ModeSwitch>();

        Scene::start();


    }

    void update() override {
        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
