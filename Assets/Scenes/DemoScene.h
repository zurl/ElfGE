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

    GameObject *human, * cube1, * cube2, * cube3, * cube4, * cube5, * light;

    DemoScene(){}

    StandardMaterial material;

    Text * text;

    std::function<void()> onclk;


    void start() override {

        ShaderManager::loadShader("fuck", "light", "exp/water");
        Shader * fuck = ShaderManager::getShader("fuck");

        //light = Prefabs::dirLight(this, glm::vec3(0, 0, 60));
        //light->transform.translate(-light->transform.getUp() * 3.0f);
        //light->transform.translate(-light->transform.getForward() * 5.0f);
        //setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        //getShadowMappingManager()->initialize();

        light = set<DirLight>(glm::vec3(0, 0, 60));
        light->transform.translate(-light->transform.getUp() * 5.0f);
        light->transform.translate(-light->transform.getForward() * 5.0f);
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();
        auto terrain = set<DemoTerrain>();

        terrain->transform.translate(glm::vec3(0, -1.5f, 0));
        auto light2 = set<PointLight>(glm::vec3(0, 0, 0));
        auto l2p = light2->getComponent<PointLighting>();
        l2p->ambient = glm::vec3(0.5f, 0.5f, 0.5f);





        human = createGameObject()
                //->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/Jarvan/run.DAE")
->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/SHIT.dae")
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                );

        auto humanModel = human->getComponent<AnimatedModel>();

        humanModel->registerAnimation("RUN", 500, 600);
        humanModel->playAnimation("RUN");

       human->transform.setScale(glm::vec3(0.01f));
        human->transform.translate(glm::vec3(3,1,0));



        auto cube1 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
        auto cube2 = set<Cube>(glm::vec3(2.0f, 3.0f, 1.0));
        auto cube3 = set<Cube>(glm::vec3(-1.0f, 3.0f, 2.0));

        //auto plane = set<Water>(glm::vec3(0.0f, 0.0f, 0.0));
//        plane->transform.setScale(glm::vec3(10));
        auto arialFont = FontManager::loadFont("Arial");

        auto camera = set<Prefabs::Camera>();

        camera->transform.setPosition(glm::vec3(-2, 2, 0));

//        cube4 = set<Cube>(glm::vec3(1,1,7));
//        cube5 = set<Cube>(glm::vec3(1,1,10));


        auto canvas = createGameObject()->createComponent<Canvas>();
//
        auto text1 = createGameObject()->createComponent<Text>("hello world!", arialFont);
//
        text1->setParent(canvas);
        text1->transform.translate(glm::vec3(20, 20, 0));
        text  = text1->getComponent<Text>();
        text->setFontColor(glm::vec3(0.5f, 0.5f, 0.0f));


        auto text2 = createGameObject()->createComponent<Text>("hello world!", arialFont);

        text2->setParent(canvas);
        text2->transform.translate(glm::vec3(40, 40, 0));
        text2->createComponent<FuckScript>(human);

        auto text2Text = text2->getComponent<Text>();

        auto image1 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/brickwall.jpg"
                ), 20.0f, 20.0f);
        image1->setParent(canvas);
        image1->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));

        onclk = [text2Text](){
            text2Text->setText("WOW HERE");
        };

        auto button = set<ImageButton>(canvas, TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/brickwall.jpg"
        ), glm::vec2(20.0f, 20.0f), glm::vec3(150, 150, 0), &onclk);


        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/skybox/");
      
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

    float x = 0;

    void update() override {
        cnt ++;
        dt += Utility::deltaTime;
        if(dt >= 1.0f){
            dt = 0;
            text->setText("FPS:" + itos(cnt));
            cnt = 0;
        }

        x++;
        if(x > 360000) x= 0;

//        human->transform.setRotation(
//                glm::vec3(human->transform.getRotation().x,
//                          human->transform.getRotation().y +0.1f,
//                          human->transform.getRotation().z));

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
