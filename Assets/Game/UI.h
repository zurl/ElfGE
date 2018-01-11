//
// Created by 张程易 on 11/01/2018.
//

#ifndef ELFGE_MYUI_H
#define ELFGE_MYUI_H

#include "UI/UI.h"
#include "StandardAssets.h"

class UI : public Prefab{

    Canvas * canvas;
    FontFace * font;
    Image * AIMScreen, * AIMCross;

    GameObject * standardUI, *developerUI;
    Text * devText1, *devText2, *devText3;

    GameObject * createText(Scene *scene, glm::vec3 pos){
        auto textGO = scene
                ->createGameObject()
                ->createComponent<Text>("hi", font);

        textGO->setParent(developerUI);
        textGO->transform.translate(pos);
        textGO->transform.setScale(glm::vec3(0.5));
        return textGO;
    }

public:
    GameObject *instantiate(Scene *scene) override {

        // init
        auto font = FontManager::loadFont("Arial");
        auto canvasGO = scene
                ->createGameObject("canvas")
                ->createComponent<Canvas>();
        canvas = canvasGO->getComponent<Canvas>();

        // standard ui

        standardUI = scene->createGameObject("standard_ui");
        standardUI->setParent(canvasGO);

        auto AIMCrossGO = scene->createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/aim.png"
                ),Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT );
        AIMCrossGO->setParent(standardUI);
        AIMCross = AIMCrossGO->getComponent<Image>();
        auto AIMScreenGO = scene->createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/aim.png"
                ),Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT );
        AIMScreen = AIMScreenGO->getComponent<Image>();
        AIMScreenGO->setParent(standardUI);

        // developer ui

        developerUI = scene->createGameObject("developer_ui");
        developerUI->setParent(canvasGO);

        auto devText1GO = createText(scene, glm::vec3(20, 20, 0));
        auto devText2GO = createText(scene, glm::vec3(20, 20, 0));
        auto devText3GO = createText(scene, glm::vec3(20, 20, 0));
        devText1 = devText1GO->getComponent<Text>();
        devText2 = devText2GO->getComponent<Text>();
        devText3 = devText3GO->getComponent<Text>();
        

        return canvasGO;
    }

    Image *getAIMScreen() const {
        return AIMScreen;
    }

    Image *getAIMCross() const {
        return AIMCross;
    }

    Text *getDevText1() const {
        return devText1;
    }

    Text *getDevText2() const {
        return devText2;
    }

    Text *getDevText3() const {
        return devText3;
    }

};

#endif //ELFGE_MYUI_H
