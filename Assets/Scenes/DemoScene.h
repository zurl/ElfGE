//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEMOSCENE_H
#define ELFGE_DEMOSCENE_H


#include "GameEngine.h"
#include "StandardAssets.h"
#include "UI/UI.h"
#include "../Prefabs.h"
#include "../Scripts/DeveloperScript.h"
#include "../Prefab/PlainText.h"
#include "../RealCamera.h"
#include "../FuckScript.h"

using namespace Prefabs;

class DemoScene : public Scene {

public:

    GameObject *human, *cube1, *cube2, *cube3, *camera , *light ,* EnemyGroup;

    Terrain * terr;

    DemoScene() {}

    StandardMaterial material;

    Text *text;

    std::function<void()> onclk;

    //std::list<GameObject *> EnemyGroup;

    float humanspeed = 0.05f;
    void start() override {
        //light
        light = set<DirLight>(glm::vec3(0, 0, 60));
        light->transform.translate(-light->transform.getUp() * 5.0f);
        light->transform.translate(-light->transform.getForward() * 5.0f);
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();

        //terrain
        auto terrain = set<DemoTerrain>();
        terr = terrain->getComponent<Terrain>();
        terrain->transform.translate(glm::vec3(0, -1.5f, 0));

        //point light
        auto light2 = set<PointLight>(glm::vec3(0, 0, 0));
        auto l2p = light2->getComponent<PointLighting>();
        l2p->ambient = glm::vec3(0.5f, 0.5f, 0.5f);

        EnemyGroup = createGameObject();

        auto skeleton =  createGameObject()
                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/fhe/Assets/sb2.dae")
               // ->createComponent<AnimationCond>()
                //->createComponent<EnemyCond>(5,1, human)
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                );

        skeleton->transform.setScale(glm::vec3(0.03f));
        //skeleton->setParent(EnemyGroup);

        auto skeletonModel = skeleton->getComponent<AnimatedModel>();
        skeletonModel->registerAnimation("hello", 5, 100);
        skeletonModel->playAnimation("hello");


        //human
        human = createGameObject()
                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/SHIT.dae")
                ->createComponent<AnimationCond>()
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                );

        //human animation
        auto humanModel = human->getComponent<AnimatedModel>();

        humanModel->registerAnimation("IDLE", 50, 90);
        humanModel->registerAnimation("RUN_WITH_GUN", 600, 614);
        humanModel->registerAnimation("JUMP", 301, 313);
        humanModel->registerAnimation("SHOOT", 375, 460);
        humanModel->registerAnimation("DOWN", 330, 350);
        humanModel->registerAnimation("RUN_DOWN", 471, 488);
        humanModel->registerAnimation("DIE", 685, 705);


        //humanModel->playAnimation("RUN");

        human->transform.setScale(glm::vec3(0.01f));
        human->transform.translate(glm::vec3(3, 1, 0));
        human->transform.rotate(glm::vec3(0,1,0), -glm::half_pi<float>());

        human->getComponent<AnimationCond>()->play(0);



       // EnemyGroup = new std::list<GameObject *>();
        cube1 = set<Cube>(glm::vec3(0.0f, 1.0f, 0.0))->createComponent<EnemyCond>(5,1, human);
        cube2 = set<Cube>(glm::vec3(2.0f, 1.0f, 1.0))->createComponent<EnemyCond>(5,1, human);
        cube3 = set<Cube>(glm::vec3(-1.0f, 1.0f, 2.0))->createComponent<EnemyCond>(5,1, human);
        cube1->setParent(EnemyGroup);
        cube2->setParent(EnemyGroup);
        cube3->setParent(EnemyGroup);
//        EnemyGroup.push_back(cube1);
//        EnemyGroup.push_back(cube2);
//        EnemyGroup.push_back(cube3);




        auto arialFont = FontManager::loadFont("Arial");
        auto canvas = createGameObject()->createComponent<Canvas>();

//        auto text1 = createGameObject()->createComponent<Text>("hello world!", arialFont);
//        text1->setParent(canvas);
//        text1->transform.translate(glm::vec3(20, 20, 0));
//        text = text1->getComponent<Text>();
//        text->setFontColor(glm::vec3(0.5f, 0.5f, 0.0f));
//
//
        auto text2 = createGameObject()->createComponent<Text>("hello world!", arialFont);
        text2->setParent(canvas);
        text2->transform.translate(glm::vec3(40, 40, 0));
        text2->createComponent<FuckScript>(human);
        auto text2Text = text2->getComponent<Text>();

        //shoot point
        auto image1 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/brickwall.jpg"
                ), 20.0f, 20.0f);
        image1->setParent(canvas);
        image1->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));

        //aim camera
        auto image2 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/aim.png"
                ),Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT );
        image2->setParent(canvas);
        image2->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));
        image2->transform.translate(glm::vec3(10000,0, 0));

        camera = createGameObject()->createComponent<RealCamera>();
        camera->getComponent<RealCamera>()->setPlayerImage(human, image2);
        setCamera(camera->getComponent<RealCamera>());

//        camera = set<Prefabs::Camera>();
        //camera->transform.setPosition(glm::vec3(0, 6, 0));

//        auto dt1 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 20, 0), 0.5);
//        auto dt2 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 60, 0), 0.5);
//        auto dt3 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 100, 0), 0.5);
//
//        auto developer = createGameObject()
//        ->createComponent<DeveloperScript>(
//                dt3->getComponent<Text>(),
//                dt2->getComponent<Text>(),
//                dt1->getComponent<Text>());



        //click button
//        onclk = [text2Text]() {
//            text2Text->setText("WOW HERE");
//        };
//        auto button = set<ImageButton>(canvas, TextureManager::loadTexture2D(
//                Utility::RESOURCE_PREFIX + "Textures/brickwall.jpg"
//        ), glm::vec2(20.0f, 20.0f), glm::vec3(150, 150, 0), &onclk);


        //skybox
        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/skybox/");

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
        //count fps
//        cnt++;
//        dt += Utility::deltaTime;
//        if (dt >= 1.0f) {
//            dt = 0;
//            text->setText("FPS:" + itos(cnt));
//            cnt = 0;
//        }
//        x++;
//        if (x > 360000) x = 0;

        cube1->transform.rotate(glm::vec3(0,1,0), 0.01);


        //human move
        if (glfwGetKey(Utility::window, GLFW_KEY_C) == GLFW_PRESS){
            if(glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS ||
               glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
                human->getComponent<AnimationCond>()->play(5);
                if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS){
                    human->transform.translate(humanspeed * human->transform.getRight());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS){
                    human->transform.translate(-humanspeed * human->transform.getRight());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS){
                    human->transform.translate(humanspeed * human->transform.getForward());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
                    human->transform.translate(-humanspeed * human->transform.getForward());
                }
            }
            else{
                human->getComponent<AnimationCond>()->play(4);
            }

        }
        else{
            if(glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS ||
                    glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS ||
                    glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS ||
                    glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
                human->getComponent<AnimationCond>()->play(1);
                if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS){
                    human->transform.translate(humanspeed * human->transform.getRight());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS){
                    human->transform.translate(-humanspeed * human->transform.getRight());
                }

                if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS){
                    human->transform.translate(humanspeed * human->transform.getForward());
                }
                if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
                    human->transform.translate(-humanspeed * human->transform.getForward());
                }
            }
            else if(glfwGetKey(Utility::window, GLFW_KEY_SPACE) == GLFW_PRESS){
                human->getComponent<AnimationCond>()->play(2);
            }
            else{
                human->getComponent<AnimationCond>()->play(0);
            }

        }


        //move camera
//        if (glfwGetKey(Utility::window, GLFW_KEY_Q) == GLFW_PRESS)
//
//            camera->transform.rotate(camera->transform.getUp(), 0.05);


        printf("update\n");

//        for(std::list<GameObject *>::iterator it = EnemyGroup.begin();it!= EnemyGroup.end();it++){
//            (*it)->getComponent<EnemyCond>()->move();
//        }
//        cube1->getComponent<EnemyCond>()->move();
        for(GameObject * x : EnemyGroup->getChildren()){
            printf("%p %p", cube1, x);
            x->getComponent<EnemyCond>()->move();
        }

        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
