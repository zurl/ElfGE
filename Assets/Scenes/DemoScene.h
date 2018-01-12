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
#include "../Game/BasicObject.h"
#include "../Game/Land.h"
#include "../LJK/EnemyCond.h"
#include "../Game/UIManager.h"
#include "../Scripts/ModeSwitch.h"
#include "../Scripts/FollowHuman.h"
#include "../Game/LandLight.h"
#include "../Scripts/EnemyScript.h"

using namespace Prefabs;

class DemoScene : public Scene {

public:


    UIManager ui;
    GameObject *camera, *light, *human;

    DemoScene() {}


    void start() override {
        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/skybox/", "jpg");

        auto terrain = set<Land>();

        human = set<Human>(
                Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/human.dae",
                terrain->getComponent<Terrain>()
        );

        auto light = set<LandLight>(human);

        auto obj = set<BasicObject>();
        obj->transform.setPosition(glm::vec3(0, 5, 0));

        ui.instantiate(this);

        camera = createGameObject()
                ->createComponent<ThirdPlayerCamera>(human->getParent(), ui.getAIMScreen()->getGameObject());
        setCamera(camera->getComponent<ThirdPlayerCamera>());
        camera->setParent(human->getParent());


        auto shit = createGameObject()
                ->createComponent<DeveloperScript>(&ui, human->getParent(), light);

        auto ModeSwitcher = createGameObject()
                ->createComponent<ModeSwitch>();

        auto EnemyFactory = createGameObject("EnemyFactory")
        ->createComponent<EnemyScript>(human, terrain->getComponent<Terrain>());

        Scene::start();


    }
    char buf[256];
    void update() override{
        glm::vec3 pos = human->getWorldPosition();
        sprintf(buf, "%f,%f,%f", pos.x, pos.y, pos.z);
        ui.getStdText1()->setText(buf);
        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
