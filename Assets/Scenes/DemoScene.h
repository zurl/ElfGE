//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEMOSCENE_H
#define ELFGE_DEMOSCENE_H


#include "GameEngine.h"
#include "StandardAssets.h"
#include "UI/UI.h"
#include "../Prefabs.h"
#include "../Scripts/FuckScript.h"
#include "../Prefab/PlainText.h"
#include "../Scripts/DeveloperScript.h"

using namespace Prefabs;

class DemoScene : public Scene {

public:

    GameObject *human, *cube1, *cube2, *cube3, *cube4, *cube5, *light;

    DemoScene() {}

    StandardMaterial material;

    Text *text;

    std::function<void()> onclk;
    std::function<void(double)> oncg;

    void start() override {


        light = set<DirLight>(glm::vec3(0, 0, 60));
        light->transform.translate(-light->getWorldUp() * 5.0f);
        light->transform.translate(-light->getWorldForward() * 5.0f);
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();
        auto terrain = set<DemoTerrain>();

        terrain->transform.translate(glm::vec3(0, -1.5f, 0));
        auto light2 = set<PointLight>(glm::vec3(0, 0, 0));
        auto l2p = light2->getComponent<PointLighting>();
        l2p->ambient = glm::vec3(0.5f, 0.5f, 0.5f);

        Config::Hack::hack = 1;
        human = createGameObject()
                //->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/Jarvan/run.DAE")
                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/SHIT.dae")
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                );
        Config::Hack::hack = 0;

        auto humanModel = human->getComponent<AnimatedModel>();

        humanModel->registerAnimation("RUN", 500, 600);
        humanModel->playAnimation("RUN");

        human->transform.setScale(glm::vec3(0.01f));
        human->transform.translate(glm::vec3(3, 1, 0));


        auto cube1 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
        auto rnd = cube1->getComponent<Renderer>();
        rnd->setSelected(true);


        auto cube2 = set<Cube>(glm::vec3(2.0f, 3.0f, 1.0));
        auto cube3 = set<Cube>(glm::vec3(-1.0f, 3.0f, 2.0));

        //Config::Hack::hack = 1;
//        human = createGameObject()
//                //->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/Jarvan/run.DAE")
//                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/SHIT.dae")
//                ->createComponent<Renderer>(
//                        &material,
//                        ShaderManager::getShader("light_with_directional_shadow_anim")
//                );
//        Config::Hack::hack = 0;
////
//        auto humanModel = human->getComponent<AnimatedModel>();
////
//        humanModel->registerAnimation("RUN", 500, 600);
//        humanModel->playAnimation("RUN");
////
//        human->transform.setScale(glm::vec3(0.01f));
//        human->transform.translate(glm::vec3(3, 1, 0));


//        auto cube1 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
//        auto cube2 = set<Cube>(glm::vec3(2.0f, 3.0f, 1.0));
//        auto cube3 = set<Cube>(glm::vec3(-1.0f, 3.0f, 2.0));

//        plane->transform.setScale(glm::vec3(10));
        auto arialFont = FontManager::loadFont("Arial");
//        auto water = createGameObject()
//                ->createComponent<WaterRenderer>();
//        water->transform.setPosition(glm::vec3(0,0,0));
//        water->transform.rotate(Transform::right, glm::pi<float>());
        auto camera = set<Prefabs::Camera>();

        camera->transform.setPosition(glm::vec3(-2, 2, 0));

//        cube4 = set<Cube>(glm::vec3(1,1,7));
//        cube5 = set<Cube>(glm::vec3(1,1,10));

        std::cerr<<"Draw Grass!!"<<std::endl;
        auto grass = createGameObject()->createComponent<GrassRenderer>();
//        grass->transform.setScale(glm::vec3(1,1,1));
        auto canvas = createGameObject()->createComponent<Canvas>();
//
        //auto text1 = createGameObject()->createComponent<Text>("hello world!", arialFont);
//
//        text1->setParent(canvas);
//        text1->transform.translate(glm::vec3(20, 20, 0));
//        text = text1->getComponent<Text>();
//        text->setFontColor(glm::vec3(0.5f, 0.5f, 0.0f));
//

//        auto text2 = createGameObject()->createComponent<Text>("hello world!", arialFont);
//
//        text2->setParent(canvas);
//        text2->transform.translate(glm::vec3(40, 40, 0));
//        text2->createComponent<FuckScript>(human);

        //auto text2Text = text2->getComponent<Text>();

        auto image1 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/brickwall.jpg"
                ), 20.0f, 20.0f);
        image1->setParent(canvas);
        image1->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));

//        onclk = [text2Text]() {
//            text2Text->setText("WOW HERE");
//        };
//
//        auto img = TextureManager::loadTexture2D(
//                Utility::RESOURCE_PREFIX + "Textures/cube_specular.png"
//        );
//
//        auto button = set<ImageButton>(
//                canvas, img,
//                glm::vec2(20.0f, 20.0f), glm::vec3(150, 150, 0), &onclk);

//        oncg = [text2Text](double x) {
//            text2Text->setText("WOW HERE" + std::to_string(x));
//        };

//        auto scrollbar = set<ScrollBar>(
//                canvas, img, img,
//                glm::vec3(300, 300, 0),
//                glm::vec2(500, 40), glm::vec2(20, 50),
//                &oncg
//        );

        auto axisX = set<Cube>(glm::vec3(0.0f, 0.0f, 0.0f));
        auto axisY = set<Cube>(glm::vec3(0.0f, 0.0f, 0.0f));
        auto axisZ = set<Cube>(glm::vec3(0.0f, 0.0f, 0.0f));
        axisX->transform.setScale(glm::vec3(1.0f, 0.05f, 0.05f));
        axisY->transform.setScale(glm::vec3(0.05f, 1.0f, 0.05f));
        axisZ->transform.setScale(glm::vec3(0.05f, 0.05f, 1.0f));
        auto cobj = new GameObject("controller");
        axisX->setParent(cobj);
        axisY->setParent(cobj);
        axisZ->setParent(cobj);
        cobj->setParent(nullptr);
        cobj->start();


        auto dt1 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 20, 0), 0.5);
        auto dt2 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 60, 0), 0.5);
        auto dt3 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 100, 0), 0.5);

        auto developer = createGameObject()
        ->createComponent<DeveloperScript>(
                dt3->getComponent<Text>(),
                dt2->getComponent<Text>(),
                dt1->getComponent<Text>(),
                cobj
        );

        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/skybox/", "jpg");

        Scene::start();
    }

    float dir = 0.01f;
    int cnt = 0;
    float dt;

    std::string itos(int i) {
        std::ostringstream iss;
        iss << i;
        return iss.str();
    }

    float x = 0;

    void update() override {
//        cnt++;
//        dt += Utility::deltaTime;
//        if (dt >= 1.0f) {
//            dt = 0;
//            text->setText("FPS:" + itos(cnt));
//            cnt = 0;
//        }
//
//        x++;
//        if (x > 360000) x = 0;

        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
