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
#include "../Scripts/ShootScript.h"
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
#include "../Scripts/BoomScript.h"

using namespace Prefabs;

class DemoScene : public Scene {

public:


    UIManager ui;
    GameObject *camera, *human;

    DemoScene() {}


    void start() override {
        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/ame_siege/", "png");

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
                ->createComponent<ThirdPlayerCamera>(human->getParent(), ui.getAIMScreen()->getGameObject(), ui.getAIMCross()->getGameObject());
        setCamera(camera->getComponent<ThirdPlayerCamera>());
        camera->setParent(human->getParent());

        auto enemy = createGameObject()
                ->createComponent<EnemyScript>(human, terrain->getComponent<Terrain>());

        auto GlobalObject = createGameObject()
                ->createComponent<DeveloperScript>(&ui, human->getParent(), light)
                ->createComponent<ModeSwitch>()
                ->createComponent<ShootScript>(human->getParent())
                ->createComponent<BoomScript>(enemy, human, ui.getCenterText());

        auto Basics = set<BasicObject>();

        Scene::start();


    }

    char buf[256];

    int cnt = 0;
    float all = 0;


    void update() override {
        if (cnt == 30) {
            cnt = 0;
            glm::vec3 pos = human->getWorldPosition();
            sprintf(buf, "pos: %.2f,%.2f,%.2f", pos.x, pos.y, pos.z);
            ui.getStdText1()->setText("FPS:" + std::to_string(30.0f / all) + "," + buf);
            all = 0;
        }
        cnt++;
        all += Utility::deltaTime;

        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
