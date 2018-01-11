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
#include "../Prefab/BasicObject.h"

using namespace Prefabs;

class DemoScene : public Scene {

public:

    GameObject  *ib, *dt1, *human, *realhuman, *camera,*house, *door,*cube1, *cube2, *cube3, *cube4, *cube5, *light, *foller;

    RigidBody * humanrg;

    Terrain * tr;

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
        light->transform.setPosition(glm::vec3(0, 15.0f, 0));
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();
        auto terrain = set<DemoTerrain>();
        tr = terrain->getComponent<Terrain>();

        auto grass = createGameObject("grass")
        ->createComponent<GrassRenderer>();


       // printf("123");
       // printf("1234");

//
//        terrain->transform.translate(glm::vec3(0, -1.5f, 0));
//        auto light2 = set<PointLight>(glm::vec3(0, 0, 0));
//        auto l2p = light2->getComponent<PointLighting>();
//        l2p->ambient = glm::vec3(0.5f, 0.5f, 0.5f);


        auto sample = set<BasicObject>();

        Config::Hack::hack = 1;
        
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
        float x = realhuman->transform.getLocalPosition().x;
        float z = realhuman->transform.getLocalPosition().z;
        realhuman->transform.setPosition(
               glm::vec3( x,tr->getHeight(x, z) ,z)
        );

        light->transform.setPosition(
                glm::vec3( x + 3.0f,15 ,z + 3.0f)
        );

        camera->transform.setPosition(
                - realhuman->getWorldForward() * 5.0f + glm::vec3(0.0f, 6.0f, 0.0f)
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



        if(mode) Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
