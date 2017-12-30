//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_DEMOSCENE_H
#define ELFGE_DEMOSCENE_H


#include "GameEngine.h"
#include "StandardAssets.h"
#include "UI/UI.h"
#include "../Prefabs.h"
#include "../Prefab/PlainText.h"
#include "../Scripts/DeveloperScript.h"
#include "../Scripts/FuckScript.h"
#include "../LJK/AnimationCond.h"

using namespace Prefabs;

class DemoScene : public Scene {

public:

    GameObject *dt1, *human, *realhuman, *camera, *cube1, *cube2, *cube3, *cube4, *cube5, *light, *foller;

    RigidBody * humanrg;

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

        printf("123");
        printf("1234");

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

        humanModel->playAnimation("RUN_WITH_GUN");


        human->transform.rotate(glm::vec3(0,1,0), glm::half_pi<float>());




        auto canvas = createGameObject()->createComponent<Canvas>();

        auto image2 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/aim.png"
                ),Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT );
        image2->setParent(canvas);
        image2->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));
        image2->transform.translate(glm::vec3(10000,0, 0));

        human->getComponent<AnimationCond>()->play(0);


        realhuman = createGameObject("human")
                ->createComponent<CharacterController>()
                ->createComponent<RigidBody>()
                ->createComponent<AABBCollider>(glm::vec3(0.6f, 2.1f, 0.6f) / 2.0f,
                                                glm::vec3(0.0f, 1.0f, 0.0f),false);

        realhuman->transform.translate(glm::vec3(3, 1, 0));
        human->setParent(realhuman);

        humanrg = human->getComponent<RigidBody>();

        camera = createGameObject()
                ->createComponent<FirstPlayerCamera>();
        setCamera(camera->getComponent<FirstPlayerCamera>());
        camera->setParent(realhuman);


//        camera = createGameObject()->createComponent<RealCamera>();
//        camera->getComponent<RealCamera>()->setPlayerImage(human, image2);
//        setCamera(camera->getComponent<RealCamera>());
//
//        camera->transform.setPosition(glm::vec3(0, 6, 0));

        foller = createGameObject("cube")
                ->createComponent<DefaultModel>(
                        new CubeMesh("bricks2.jpg", "bricks2.jpg", "bricks2_normal.jpg", "bricks2_disp.jpg"))
                ->createComponent<Renderer>(
                        &material, ShaderManager::getShader("light_ds_pm"))
                ->createComponent<AABBCollider>(true, false);



        Config::Hack::hack = 0;



        auto cube1 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));


        auto rnd = cube1->getComponent<Renderer>();
        rnd->setSelected(true);


        auto cube2 = set<Cube>(glm::vec3(2.0f, 3.0f, 1.0));
        auto cube3 = set<Cube>(glm::vec3(-1.0f, 3.0f, 2.0));




        auto arialFont = FontManager::loadFont("Arial");


        auto image1 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/brickwall.jpg"
                ), 20.0f, 20.0f);
        image1->setParent(canvas);
        image1->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));


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
        //cobj->start();


        dt1 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 20, 0), 0.5);
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
    float humanspeed = 0.05f;

    void update() override {
//        dt1->getComponent<Text>()->setText(
//                "Position : " + std::to_string(human->getWorldPosition().x) + ","
//                + std::to_string(human->getWorldPosition().y) + ","
//                + std::to_string(human->getWorldPosition().z) + ",");

        if (glfwGetKey(Utility::window, GLFW_KEY_U) == GLFW_PRESS){
            auto cld = realhuman->getComponent<AABBCollider>();
            auto offset = (cld->min + cld->max) * 0.5f;
            auto size = (cld->max - cld->min) * 0.5f;
            auto t = size.z;
            size.z = size.x;
            size.z = t;
            foller->transform.setPosition(offset);
            foller->transform.setScale(size * 2.0f);
        }

        camera->transform.setPosition(
                - realhuman->getWorldForward() * 5.0f + glm::vec3(0.0f, 2.0f, 0.0f)
        );

        //human move
//        if (glfwGetKey(Utility::window, GLFW_KEY_C) == GLFW_PRESS){
//            if(glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS ||
//               glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS ||
//               glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS ||
//               glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
//                human->getComponent<AnimationCond>()->play(5);
//
//            }
//            else{
//                human->getComponent<AnimationCond>()->play(4);
//            }
//
//        }
//        else{
//            if(glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS ||
//               glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS ||
//               glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS ||
//               glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
//                human->getComponent<AnimationCond>()->play(1);
//                if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS){
//                    humanrg->translate(humanspeed * human->transform.getLocalRight());
//                }
//                if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS){
//                    humanrg->translate(-humanspeed * human->transform.getLocalRight());
//                }
//
//                if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS){
//                    humanrg->translate(humanspeed * human->transform.getLocalForward());
//                }
//                if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS){
//                    humanrg->translate(-humanspeed * human->transform.getLocalForward());
//                }
//            }
//            else if(glfwGetKey(Utility::window, GLFW_KEY_SPACE) == GLFW_PRESS){
//                human->getComponent<AnimationCond>()->play(2);
//            }
//            else{
//                human->getComponent<AnimationCond>()->play(0);
//            }
//
//        }



        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
