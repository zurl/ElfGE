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
#include "../LJK/RealCamera.h"
#include "../LJK/EnemyCond.h"


using namespace Prefabs;

class DemoScene : public Scene {

public:

    GameObject *dt1, *human, *realhuman, *camera, *cube1, *cube2, *cube3, *cube4, *cube5, *light, *foller,
            * enemy, * enemy2,  *realenemy, * enemyGroup, * Boom, *pfobj, *ib, * woodButton, *BrickButton, * MetalButton
    , * StoneButton, * Develop;

    RigidBody * humanrg;
    ParticleFactory * pf;
    DemoScene() {}

    StandardMaterial material;

    Text *text;

    std::function<void(double)> oncg1;
    std::function<void(double)> oncg2;
    std::function<void(double)> oncg3;

    std::function<void()> onclk1;
    std::function<void()> onclk2;
    std::function<void()> onclk3;
    std::function<void()> onclk4;

    void start(void (*pFunction)()) {

        light = set<DirLight>(glm::vec3(0, 0, 60));
        light->transform.translate(-light->getWorldUp() * 5.0f);
        light->transform.translate(-light->getWorldForward() * 5.0f);
        setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        getShadowMappingManager()->initialize();

        auto Develop = createGameObject()->createComponent<DeveloperScript>();


        auto terrain = set<DemoTerrain>();
        terrain->transform.translate(glm::vec3(0, -1.5f, 0));
        auto light2 = set<PointLight>(glm::vec3(0, 0, 0));
        auto l2p = light2->getComponent<PointLighting>();
        l2p->ambient = glm::vec3(0.5f, 0.5f, 0.5f);

        Config::Hack::hack = 1;

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
        humanModel->registerAnimation("RUN", 600, 614);
        humanModel->registerAnimation("JUMP", 301, 313);
        humanModel->registerAnimation("SHOOT", 375, 460);
        humanModel->registerAnimation("DOWN", 330, 350);
        humanModel->registerAnimation("RUN_DOWN", 471, 488);
        humanModel->registerAnimation("DIE", 685, 705);

        human->transform.rotate(glm::vec3(0,1,0), glm::half_pi<float>());
        //humanModel->playAnimation("RUN_WITH_GUN");
        human->getComponent<AnimationCond>()->play(0);


        realhuman = createGameObject("human")
                ->createComponent<CharacterController>(human)
                ->createComponent<RigidBody>()
                ->createComponent<AABBCollider>(glm::vec3(0.6f, 2.1f, 0.6f) / 2.0f,
                                                glm::vec3(0.0f, 1.0f, 0.0f),false);

        realhuman->transform.translate(glm::vec3(3, 1, 0));
        human->setParent(realhuman);



        //set the enemy group
        enemyGroup = createGameObject();

        //enemy one
        enemy = createGameObject("enemy")
                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/fhe/Assets/sb.dae")
                ->createComponent<AnimationCond>()
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                )
                ->createComponent<RigidBody>()
                ->createComponent<AABBCollider>(glm::vec3(0.6f, 2.1f, 0.6f) / 2.0f,
                                                glm::vec3(0.0f, 1.0f, 0.0f),false)
                ->createComponent<EnemyCond>(5, 1, realhuman);

        auto enemyModel = enemy->getComponent<AnimatedModel>();

        enemyModel->registerAnimation("IDLE", 50, 100);
        enemyModel->registerAnimation("RUN", 325, 350);
        enemyModel->registerAnimation("DIE", 200, 215);
        enemyModel->registerAnimation("HIT", 145, 160);
        enemyModel->registerAnimation("WALK", 360, 389);

        enemyModel->playAnimation("IDLE");

        enemy->transform.translate(glm::vec3(3, 1, 0));
        enemy->setParent(enemyGroup);

        //enemy two
        enemy2 = createGameObject("enemy2")
                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/fhe/Assets/sb.dae")
                ->createComponent<AnimationCond>()
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                )
                ->createComponent<RigidBody>()
                ->createComponent<AABBCollider>(glm::vec3(0.6f, 2.1f, 0.6f) / 2.0f,
                                                glm::vec3(0.0f, 1.0f, 0.0f),false)
                ->createComponent<EnemyCond>(5, 1, realhuman);

        auto enemyModel2 = enemy2->getComponent<AnimatedModel>();

        enemyModel2->registerAnimation("IDLE", 50, 100);
        enemyModel2->registerAnimation("RUN", 325, 350);
        enemyModel2->registerAnimation("DIE", 200, 215);
        enemyModel2->registerAnimation("HIT", 145, 160);
        enemyModel2->registerAnimation("WALK", 360, 389);

        enemyModel2->playAnimation("IDLE");

        enemy2->transform.translate(glm::vec3(20, 1, 0));
        enemy2->setParent(enemyGroup);



        auto canvas = createGameObject()->createComponent<Canvas>();

        auto arialFont = FontManager::loadFont("Arial");

        auto textAngle = set<PlainText>(canvas, arialFont, "Light Angle", glm::vec3(50, 440, 0), 0.5);
        auto img = TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/cube_specular.png");

        auto scrollbar = set<ScrollBar>(canvas, img, img,
                                        glm::vec3(300, 400, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg1 );

        auto textDiffuse = set<PlainText>(canvas, arialFont, "Diffuse Luminance", glm::vec3(50, 340, 0), 0.5);
        auto scrollbar2 = set<ScrollBar>(canvas, img, img,
                                         glm::vec3(300, 300, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg2 );

        auto textSpecular = set<PlainText>(canvas, arialFont, "Specular Luminance", glm::vec3(50, 240, 0), 0.5);
        auto scrollbar3 = set<ScrollBar>(canvas, img, img,
                                         glm::vec3(300, 200, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg3 );

        oncg1 = [this](double x){ light->transform.setRotation(glm::vec3(0,0,x*1.0-1.0)); };
        oncg2 = [this](double x){ light->getComponent<DirectLighting>()->diffuse = glm::vec3(10.0f *x, 10.0f*x, 10.0f*x); };
        oncg3 = [this](double x){ light->getComponent<DirectLighting>()->specular = glm::vec3(2.0f *x, 2.0f*x, 2.0f*x);  };


        auto image2 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/aim.png"
                ),Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT );
        image2->setParent(canvas);
        image2->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));
        image2->transform.translate(glm::vec3(10000,0, 0));





        camera = createGameObject()
                ->createComponent<RealCamera>();
        camera->getComponent<RealCamera>()->setPlayerImage(realhuman, image2);
        setCamera(camera->getComponent<RealCamera>());
        camera->setParent(realhuman);



        Config::Hack::hack = 0;



        auto cube1 = set<Cube>(glm::vec3(0.0f, 3.0f, 0.0));


        auto rnd = cube1->getComponent<Renderer>();
        rnd->setSelected(true);


        auto cube2 = set<Cube>(glm::vec3(2.0f, 3.0f, 1.0));
        auto cube3 = set<Cube>(glm::vec3(2.0f, 3.0f, 5.0));

        Boom = set<Cube>(glm::vec3(10000.0f, 0.0f,0.0f));

        auto fuck = createGameObject()->createComponent<FuckScript>(realhuman);


        // add text button here
        auto textTexture = set<PlainText>(canvas, arialFont, "Textures", glm::vec3(100, 140, 0), 0.5);

        unsigned int newImage1 = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/wood.jpg");
        unsigned int newImage2 = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/bricks2.jpg");
        unsigned int newImage3 = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/dalishi.jpg");
        unsigned int newImage4 = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/metal.jpg");

        woodButton = set<ImageButton>(
                canvas,
                TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/wood.jpg"
                ),
                glm::vec2(50, 50),
                glm::vec3(150, 100, 0),
                &onclk1
        );

        onclk1 = pFunction;


        BrickButton = set<ImageButton>(
                canvas,
                TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/bricks2.jpg"
                ),
                glm::vec2(50, 50),
                glm::vec3(250, 100, 0),
                &onclk2
        );

        onclk2 = [cube1, newImage2](){
            printf("hello2");
            if(cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.size() >=1){
                cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.at(0).id = newImage2;
                printf("hello!");
            }
            else{
                DefaultMesh::Texture ff(newImage2, "diffuse");
                cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.push_back(ff);
            }
        };

        MetalButton = set<ImageButton>(
                canvas,
                TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/Metal.jpg"
                ),
                glm::vec2(50, 50),
                glm::vec3(350, 100, 0),
                &onclk3
        );

        onclk3 = [cube1, newImage3](){
            if(cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.size() >=1){
                cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.at(0).id = newImage3;
            }
            else{
                DefaultMesh::Texture ff(newImage3, "diffuse");
                cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.push_back(ff);
            }
        };

        StoneButton = set<ImageButton>(
                canvas,
                TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/dalishi.jpg"
                ),
                glm::vec2(50, 50),
                glm::vec3(450, 100, 0),
                &onclk4
        );

        onclk4 = [cube1, newImage4](){
            if(cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.size() >=1){
                cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.at(0).id = newImage4;
            }
            else{
                DefaultMesh::Texture ff(newImage4, "diffuse");
                cube1->getComponent<DefaultModel>()->meshes.at(0)->textures.push_back(ff);
            }
        };






        auto image1 = createGameObject()
                ->createComponent<Image>(TextureManager::loadTexture2D(
                        Utility::RESOURCE_PREFIX + "Textures/fuck.png"
                ), 60.0f, 60.0f);
        image1->setParent(canvas);
        image1->transform.translate(glm::vec3(Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT / 2, 0));

        //particle
        pfobj = createGameObject()
                ->createComponent<ParticleFactory>();

        //pfobj->setParent(Boom);
        pf = pfobj->getComponent<ParticleFactory>();

        //Boom counting
        dt1 = set<PlainText>(canvas, arialFont, "", glm::vec3(450, 150, 0), 5);

        auto skybox = createGameObject()
                ->createComponent<SkyBox>("Textures/skybox/", "jpg");


//        Develop = createGameObject()->createComponent<DeveloperScript>(Canvas);

        Scene::start();

//        Develop->getComponent<DeveloperScript>()->setVisible(false);

        woodButton->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
        BrickButton->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
        MetalButton->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
        StoneButton->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
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
    float humanspeed = 0.05f;

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
                    woodButton->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
                    BrickButton->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
                    MetalButton->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
                    StoneButton->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
//                    Develop->getComponent<DeveloperScript>()->setVisible(false);
                    glfwSetInputMode(Utility::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                } else {
                    mode = 0;
                    mode_timer = 50;
                    woodButton->setStatus(STATUS_NORMAL);
                    BrickButton->setStatus(STATUS_NORMAL);
                    StoneButton->setStatus(STATUS_NORMAL);
                    MetalButton->setStatus(STATUS_NORMAL);
//                    Develop->getComponent<DeveloperScript>()->setVisible(true);
                    glfwSetInputMode(Utility::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
            }
        }

//        if(glfwGetKey(Utility::window, GLFW_KEY_U) == GLFW_PRESS){
//            printf("fuck");
//
//        }

        if(glfwGetKey(Utility::window, GLFW_KEY_E) == GLFW_PRESS){
            printf("Set Boom!");
            BoomCnt = 500;
            Boom->transform.setPosition(realhuman->getWorldPosition() + realhuman->getWorldForward() * 3.0f + glm::vec3(0,1.5f,0));
        }

        if(glfwGetKey(Utility::window, GLFW_KEY_UP) == GLFW_PRESS){
            light->transform.translate(light->getWorldRight());
        }

        if(glfwGetKey(Utility::window, GLFW_KEY_DOWN) == GLFW_PRESS){
            light->transform.translate(-light->getWorldRight());
        }

        if(BoomCnt>0){
            BoomCnt--;
            if(BoomCnt == 0){
                for(GameObject * e : enemyGroup->getChildren()){
                    glm::vec3 disVec = e->getWorldPosition() - Boom->getWorldPosition();
                    float dis = disVec.x * disVec.x + disVec.y * disVec.y + disVec.z * disVec.z;
                    if(dis < 10){
                        e->getComponent<EnemyCond>()->Health-=10;
                    }
                }
                pfobj->transform.setPosition(Boom->getWorldPosition());
                pf->addExplosion();
                Boom->transform.setPosition(glm::vec3(10000.0,0,0));
                dt1->getComponent<Text>()->setText("");
            }
            else if(BoomCnt <= 100){
                dt1->getComponent<Text>()->setText("1");
            }
            else if(BoomCnt <= 200){
                dt1->getComponent<Text>()->setText("2");
            }
            else if(BoomCnt <= 300){
                dt1->getComponent<Text>()->setText("3");
            }
            else if(BoomCnt <= 400){
                dt1->getComponent<Text>()->setText("4");
            }
            else if(BoomCnt <= 500){
                dt1->getComponent<Text>()->setText("5");
            }
        }




        for(GameObject * e : enemyGroup->getChildren()){
            e->getComponent<EnemyCond>()->move();
        }

        Scene::update();
    }
};


#endif //ELFGE_DEMOSCENE_H
