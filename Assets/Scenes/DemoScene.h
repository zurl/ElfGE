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
#include "../Prefab/BasicObject.h"

using namespace Prefabs;

class DemoScene : public Scene {

public:

    GameObject *ib, *dt1, *human, *realhuman, *camera,*house, *door,*cube1, *cube2, *cube3, *cube4, *cube5, *light, *foller;

    RigidBody * humanrg;

    DemoScene() {}

    StandardMaterial material;

    Text *text;

    ParticleFactory * pf;

    std::function<void()> onclk;
    std::function<void(double)> oncg;

    void start() override {
        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/skybox/", "jpg");


        light = set<DirLight>(glm::vec3(0, 0, 60));
        light->transform.translate(-light->getWorldUp() * 5.0f);
        light->transform.translate(-light->getWorldForward() * 5.0f);
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();
//        auto terrain = set<DemoTerrain>();
//
//        terrain->transform.translate(glm::vec3(0, -1.5f, 0));
        auto light2 = set<PointLight>(glm::vec3(0, 0, 0));
        auto l2p = light2->getComponent<PointLighting>();
        l2p->ambient = glm::vec3(0.5f, 0.5f, 0.5f);


        auto sample = set<BasicObject>();

        Config::Hack::hack = 1;
//        auto tree = createGameObject()
//                ->createComponent<DefaultModel>(Utility::RESOURCE_PREFIX + "Models/tree/Tree.obj")
//                ->createComponent<Renderer>(
//                        &material,
//                        ShaderManager::getShader("light_with_directional_shadow")
//                );
//
//        tree->transform.setScale(glm::vec3(0.5f));

        house = createGameObject()
                ->createComponent<DefaultModel>(Utility::RESOURCE_PREFIX + "Models/house/cabin.obj")
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("house/light_with_directional_shadow")
                );
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

//        auto wall1 = createGameObject()
//                        ->createComponent<AABBCollider>(
//                                glm::vec3(1.5f,5.0f,6.5f),
//                                glm::vec3(6.2f,3.0f,-1.0f),
//                                true,true);
//        wall1->setParent(house);
//        auto cube1 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
//        cube1->transform.setPosition(glm::vec3(6.2f,3.0f,-1.0f));
//        cube1->transform.setScale(glm::vec3(1.5f,5.0f,6.5f));
//        cube1->setParent(house);
//        auto cube2 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
//        cube2->transform.setPosition(glm::vec3(-6.2f,3.0f,-1.0f));
//        cube2->transform.setScale(glm::vec3(1.5f,5.0f,6.5f));
//        cube2->setParent(house);
//
//        auto cube3 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
//        cube3->transform.setPosition(glm::vec3(0.0f,3.0f,-4.0f));
//        cube3->transform.setScale(glm::vec3(13.2f,4.6f,1.2f));
//        cube3->setParent(house);
//
//        auto cube4 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
//        cube4->setParent(house);
//        cube4->transform.setPosition(glm::vec3(1.5f,3.0f,1.9f));
//        cube4->transform.setScale(glm::vec3(1.7f,4.6f,1.2f));
//
//        auto cube5 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
//        cube5->setParent(house);
//        cube5->transform.setPosition(glm::vec3(-3.8f,3.0f,1.9f));
//        cube5->transform.setScale(glm::vec3(5.0f,4.6f,1.2f));
////
//        auto cube6 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));
//        cube6->setParent(house);
//        cube6->transform.setPosition(glm::vec3(5.4f,3.0f,1.9f));
//        cube6->transform.setScale(glm::vec3(2.5f,4.6f,1.2f));

        human = createGameObject()
                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/SHIT.dae")
                ->createComponent<AnimationCond>()
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                );
        Config::Hack::hack = 0;

        auto pfobj = createGameObject()
                ->createComponent<ParticleFactory>();

        pfobj->setParent(human);

        pf = pfobj->getComponent<ParticleFactory>();


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


        onclk = [](){
            printf("hehe");
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

//        foller = createGameObject("cube")
//                ->createComponent<DefaultModel>(
//                        new CubeMesh("bricks2.jpg", "bricks2.jpg", "bricks2_normal.jpg", "bricks2_disp.jpg"))
//                ->createComponent<Renderer>(
//                        &material, ShaderManager::getShader("light_ds_pm"))
//                ->createComponent<AABBCollider>(true, true);


        Config::Hack::hack = 0;



//
//
//        auto rnd = cube1->getComponent<Renderer>();
//        rnd->setSelected(true);
//
//
//        auto cube2 = set<Cube>(glm::vec3(2.0f, 3.0f, 1.0));
//        auto cube3 = set<Cube>(glm::vec3(-1.0f, 3.0f, 2.0));
//
//
//
//
        auto arialFont = FontManager::loadFont("Arial");
//

        auto image1 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/brickwall.jpg"
                ), 20.0f, 20.0f);
        image1->setParent(canvas);
        image1->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));


//        auto axisX = set<Cube>(glm::vec3(0.0f, 0.0f, 0.0f));
//        auto axisY = set<Cube>(glm::vec3(0.0f, 0.0f, 0.0f));
//        auto axisZ = set<Cube>(glm::vec3(0.0f, 0.0f, 0.0f));
//        axisX->transform.setScale(glm::vec3(1.0f, 0.05f, 0.05f));
//        axisY->transform.setScale(glm::vec3(0.05f, 1.0f, 0.05f));
//        axisZ->transform.setScale(glm::vec3(0.05f, 0.05f, 1.0f));
        auto cobj = new GameObject("controller");
//        axisX->setParent(cobj);
//        axisY->setParent(cobj);
//        axisZ->setParent(cobj);
        cobj->setParent(nullptr);
        cobj->start();
//
//
        dt1 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 20, 0), 0.5);
        auto dt2 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 60, 0), 0.5);
        auto dt3 = set<PlainText>(canvas, arialFont, "hi", glm::vec3(20, 100, 0), 0.5);
//
//
        auto cb = createGameObject()
//                ->createComponent<DefaultModel>(
//                        new CubeMesh("bricks2.jpg", "bricks2.jpg", "bricks2_normal.jpg", "bricks2_disp.jpg"))
//                ->createComponent<Renderer>(
//                        &material, ShaderManager::getShader("light_ds_pm"))

        ->createComponent<DeveloperScript>(
                dt3->getComponent<Text>(),
                dt2->getComponent<Text>(),
                dt1->getComponent<Text>(),
                cobj,
                realhuman
        );
        Scene::start();


        ib->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);

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

    int mode = 1;
    int mode_timer = 0;

    void update() override {
        if(mode_timer > 0) mode_timer --;
        if (glfwGetKey(Utility::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            if(mode_timer == 0){
                if (mode == 0) {
                    mode = 1;
                    mode_timer = 50;
                    ib->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
                    glfwSetInputMode(Utility::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                } else {
                    mode = 0;
                    mode_timer = 50;
                    ib->setStatus(STATUS_NORMAL);
                    glfwSetInputMode(Utility::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
            }
        }

//        dt1->getComponent<Text>()->setText(
//                "Position : " + std::to_string(human->getWorldPosition().x) + ","
//                + std::to_string(human->getWorldPosition().y) + ","
//                + std::to_string(human->getWorldPosition().z) + ",");

        if (glfwGetKey(Utility::window, GLFW_KEY_K) == GLFW_PRESS){
            auto cld = realhuman->getComponent<AABBCollider>();
            //auto cld = ->getComponent<AABBCollider>();
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

        if(glfwGetKey(Utility::window, GLFW_KEY_U) == GLFW_PRESS){
            pf->addExplosion();
        }

        if(glfwGetKey(Utility::window, GLFW_KEY_Q) == GLFW_PRESS){
            static bool open = true;
            if(open) door->getComponent<DoorModel>()->openDoor();
            else door->getComponent<DoorModel>()->closeDoor();
            open = !open;
        }
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



        if(mode) Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
