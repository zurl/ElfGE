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
using namespace Prefabs;

class DemoScene : public Scene {

public:

    GameObject  *ib, *dt1, *human, *realhuman, *camera,*house, *door,*cube1, *cube2, *cube3, *cube4, *cube5, *light, *foller;

    RigidBody * humanrg;

    Terrain * tr;
    DemoScene() {}



    Text *text;

    ParticleFactory * pf;

    std::function<void()> onclk;
    std::function<void(double)> oncg;

    void start() override {
        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/skybox/", "jpg");

        light = set<DirLight>(glm::vec3(0, 0, 60));
        light->transform.setPosition(glm::vec3(0, 15.0f, 0));
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();

        auto terrain = set<Land>();

        //auto sample = set<BasicObject>();
        house = createGameObject()
                ->createComponent<DefaultModel>(Utility::RESOURCE_PREFIX + "Models/house/cabin.obj");

        door = createGameObject()
                ->createComponent<DoorModel>(Utility::RESOURCE_PREFIX + "Models/house/door.obj")
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("house/light_with_directional_shadow")
                )
        ->createComponent<AABBCollider>(true,false);
        door->setParent(house);
        door->transform.setScale(glm::vec3(1.1f,1.05f,1.0f));
        door->transform.setPosition(glm::vec3(2.6f,1.0f,2.2f));


        auto human = set<Human>(
                Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/human.dae",
                terrain->getComponent<Terrain>()
        );


//        //set the enemy group
//        enemyGroup = createGameObject();
//
//        //enemy one
//        enemy = createGameObject("enemy")
//                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/fhe/Assets/sb.dae")
//                ->createComponent<AnimationCond>()
//                ->createComponent<Renderer>(
//                        &material,
//                        ShaderManager::getShader("light_with_directional_shadow_anim")
//                )
//                ->createComponent<RigidBody>()
//                ->createComponent<AABBCollider>(glm::vec3(0.6f, 2.1f, 0.6f) / 2.0f,
//                                                glm::vec3(0.0f, 1.0f, 0.0f),false)
//                ->createComponent<EnemyCond>(5, 1, realhuman);
//
//        auto enemyModel = enemy->getComponent<AnimatedModel>();
//
//        enemyModel->registerAnimation("IDLE", 50, 100);
//        enemyModel->registerAnimation("RUN", 325, 350);
//        enemyModel->registerAnimation("DIE", 200, 215);
//        enemyModel->registerAnimation("HIT", 145, 160);
//        enemyModel->registerAnimation("WALK", 360, 389);
//
//        enemyModel->playAnimation("IDLE");
//
//        enemy->transform.translate(glm::vec3(3, 1, 0));
//        enemy->setParent(enemyGroup);
//
//        //enemy two
//        enemy2 = createGameObject("enemy2")
//                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/fhe/Assets/sb.dae")
//                ->createComponent<AnimationCond>()
//                ->createComponent<Renderer>(
//                        &material,
//                        ShaderManager::getShader("light_with_directional_shadow_anim")
//                )
//                ->createComponent<RigidBody>()
//                ->createComponent<AABBCollider>(glm::vec3(0.6f, 2.1f, 0.6f) / 2.0f,
//                                                glm::vec3(0.0f, 1.0f, 0.0f),false)
//                ->createComponent<EnemyCond>(5, 1, realhuman);
//
//        auto enemyModel2 = enemy2->getComponent<AnimatedModel>();
//
//        enemyModel2->registerAnimation("IDLE", 50, 100);
//        enemyModel2->registerAnimation("RUN", 325, 350);
//        enemyModel2->registerAnimation("DIE", 200, 215);
//        enemyModel2->registerAnimation("HIT", 145, 160);
//        enemyModel2->registerAnimation("WALK", 360, 389);
//
//        enemyModel2->playAnimation("IDLE");
//
//        enemy2->transform.translate(glm::vec3(20, 1, 0));
//        enemy2->setParent(enemyGroup);
//
//
//
        auto canvas = createGameObject()->createComponent<Canvas>();
//
        auto arialFont = FontManager::loadFont("Arial");
//
//        auto textAngle = set<PlainText>(canvas, arialFont, "Light Angle", glm::vec3(50, 440, 0), 0.5);
//        auto img = TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/cube_specular.png");
//
//        auto scrollbar = set<ScrollBar>(canvas, img, img,
//                                        glm::vec3(300, 400, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg1 );
//
//        auto textDiffuse = set<PlainText>(canvas, arialFont, "Diffuse Luminance", glm::vec3(50, 340, 0), 0.5);
//        auto scrollbar2 = set<ScrollBar>(canvas, img, img,
//                                         glm::vec3(300, 300, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg2 );
//
//        auto textSpecular = set<PlainText>(canvas, arialFont, "Specular Luminance", glm::vec3(50, 240, 0), 0.5);
//        auto scrollbar3 = set<ScrollBar>(canvas, img, img,
//                                         glm::vec3(300, 200, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg3 );
//
//        oncg1 = [this](double x){ light->transform.setRotation(glm::vec3(0,0,x*1.0-1.0)); };
//        oncg2 = [this](double x){ light->getComponent<DirectLighting>()->diffuse = glm::vec3(10.0f *x, 10.0f*x, 10.0f*x); };
//        oncg3 = [this](double x){ light->getComponent<DirectLighting>()->specular = glm::vec3(2.0f *x, 2.0f*x, 2.0f*x);  };


        auto image2 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/aim.png"
                ),Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT );
        image2->setParent(canvas);


        onclk = [](){
            int len = Utility::SCREEN_WIDTH * Utility::SCREEN_HEIGHT * 3;
            void * screenData = malloc(len);
            glReadPixels(0, 0,
                         Utility::SCREEN_WIDTH,
                         Utility::SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, screenData);
            stbi_write_png("saved.png",
                           Utility::SCREEN_WIDTH,
                           Utility::SCREEN_HEIGHT, 3, screenData, 0);
        };

        ib = set<ImageButton>(
                canvas,
                TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/brick2.png"
                ),
                glm::vec2(50, 50),
                glm::vec3(100, 100, 0),
                &onclk
        );

        image2->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));
        image2->transform.translate(glm::vec3(10000,0, 0));

        human->getComponent<AnimationCond>()->play(0);


        camera = createGameObject()
                ->createComponent<ThirdPlayerCamera>(human->getParent(), image2);
        setCamera(camera->getComponent<ThirdPlayerCamera>());
        camera->setParent(human->getParent());


        Scene::start();


    }

    float dir = 0.01f;
    int cnt = 0;
    float dt;
    int BoomCnt = 0;
    std::string itos(int i) {
        std::ostringstream iss;
        iss << i;
        return iss.str();
    }

    float x = 0;

    int mode = 1;
    int mode_timer = 0;
    //update
    void update() override {
        if(mode_timer > 0) mode_timer --;
        if (glfwGetKey(Utility::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            if(mode_timer == 0){
                if (mode == 0) {
                    mode = 1;
                    mode_timer = 50;
                    glfwSetInputMode(Utility::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
            }
        }

        Scene & s = *this;

//        if (glfwGetKey(Utility::window, GLFW_KEY_K) == GLFW_PRESS){
//            auto cld = realhuman->getComponent<AABBCollider>();
//            //auto cld = ->getComponent<AABBCollider>();
//            auto offset = (cld->min + cld->max) * 0.5f;
//            auto size = (cld->max - cld->min) * 0.5f;
//            auto t = size.z;
//            size.z = size.x;
//            size.z = t;
//            foller->transform.setPosition(offset);
//            foller->transform.setScale(size * 2.0f);
//        }


        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
