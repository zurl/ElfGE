//
// Created by 张程易 on 23/12/2017.
//

#include "DeveloperScript.h"
#include "ShootScript.h"

void DeveloperScript::start() {

    shootScript = getGameObject()->getComponent<ShootScript>();

    enter = std::bind(&DeveloperScript::onClickEnter, this);

    //add by ljk
    auto arialFont = FontManager::loadFont("Arial");

    auto textAngle = instantiate<PlainText>(UIRoot, arialFont, "Light Angle", glm::vec3(50, 540, 0), 0.5);
    auto img = TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/cube_specular.png");

    auto scrollbar = instantiate<ScrollBar>(UIRoot, img, img,
                                            glm::vec3(300, 500, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg1);

    auto textDiffuse = instantiate<PlainText>(UIRoot, arialFont, "Diffuse Luminance", glm::vec3(50, 440, 0), 0.5);
    auto scrollbar2 = instantiate<ScrollBar>(UIRoot, img, img,
                                             glm::vec3(300, 400, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg2);

    auto textSpecular = instantiate<PlainText>(UIRoot, arialFont, "Specular Luminance", glm::vec3(50, 340, 0), 0.5);
    auto scrollbar3 = instantiate<ScrollBar>(UIRoot, img, img,
                                             glm::vec3(300, 300, 0), glm::vec2(500, 40), glm::vec2(20, 50), &oncg3);


    oncg1 = [this](double x) { light->transform.setRotation(glm::vec3(0, 0, x * 1.0 - 1.0)); };
    oncg2 = [this](double x) {
        light->getComponent<DirectLighting>()->diffuse = glm::vec3(1.0f * x, 1.0f * x, 1.0f * x);
    };
    oncg3 = [this](double x) {
        light->getComponent<DirectLighting>()->specular = glm::vec3(0.4f * x, 0.4f * x, 0.4f * x);
    };


    // add text button here
    auto textTexture = instantiate<PlainText>(UIRoot, arialFont, "Textures", glm::vec3(100, 50, 0), 0.5);

    unsigned int newImage1 = TextureManager::loadTexture2D(
            Utility::RESOURCE_PREFIX + "Textures/wood.jpg");
    unsigned int newImage2 = TextureManager::loadTexture2D(
            Utility::RESOURCE_PREFIX + "Textures/bricks2.jpg");
    unsigned int newImage3 = TextureManager::loadTexture2D(
            Utility::RESOURCE_PREFIX + "Textures/dalishi.jpg");
    unsigned int newImage4 = TextureManager::loadTexture2D(
            Utility::RESOURCE_PREFIX + "Textures/metal.jpg");

    woodButton = instantiate<ImageButton>(
            UIRoot,
            TextureManager::loadTexture2D(
                    Utility::RESOURCE_PREFIX + "Textures/wood.jpg"
            ),
            glm::vec2(50, 50),
            glm::vec3(150, 150, 0),
            &onclk1
    );

    onclk1 = [this, newImage1]() {
        GameObject *now = target;
        if (now != nullptr) {
            if (now->getComponent<DefaultModel>()->meshes.at(0)->textures.size() >= 1) {
                now->getComponent<DefaultModel>()->meshes.at(0)->textures.at(0).id = newImage1;
            } else {
                DefaultMesh::Texture ff(newImage1, "diffuse");
                now->getComponent<DefaultModel>()->meshes.at(0)->textures.push_back(ff);
            }
        }
    };


    BrickButton = instantiate<ImageButton>(
            UIRoot,
            TextureManager::loadTexture2D(
                    Utility::RESOURCE_PREFIX + "Textures/bricks2.jpg"
            ),
            glm::vec2(50, 50),
            glm::vec3(250, 150, 0),
            &onclk2
    );

    onclk2 = [this, newImage2]() {
        GameObject *now = target;
        if (now != nullptr) {
            if (now->getComponent<DefaultModel>()->meshes.at(0)->textures.size() >= 1) {
                now->getComponent<DefaultModel>()->meshes.at(0)->textures.at(0).id = newImage2;
            } else {
                DefaultMesh::Texture ff(newImage2, "diffuse");
                now->getComponent<DefaultModel>()->meshes.at(0)->textures.push_back(ff);
            }
        }
    };

    MetalButton = instantiate<ImageButton>(
            UIRoot,
            TextureManager::loadTexture2D(
                    Utility::RESOURCE_PREFIX + "Textures/Metal.jpg"
            ),
            glm::vec2(50, 50),
            glm::vec3(350, 150, 0),
            &onclk3
    );

    onclk3 = [this, newImage3]() {
        GameObject *now = target;
        if (now != nullptr) {
            if (now->getComponent<DefaultModel>()->meshes.at(0)->textures.size() >= 1) {
                now->getComponent<DefaultModel>()->meshes.at(0)->textures.at(0).id = newImage3;
            } else {
                DefaultMesh::Texture ff(newImage3, "diffuse");
                now->getComponent<DefaultModel>()->meshes.at(0)->textures.push_back(ff);
            }
        }
    };

    StoneButton = instantiate<ImageButton>(
            UIRoot,
            TextureManager::loadTexture2D(
                    Utility::RESOURCE_PREFIX + "Textures/dalishi.jpg"
            ),
            glm::vec2(50, 50),
            glm::vec3(450, 150, 0),
            &onclk4
    );

    onclk4 = [this, newImage4]() {
        GameObject *now = target;
        if (now != nullptr) {
            if (now->getComponent<DefaultModel>()->meshes.at(0)->textures.size() >= 1) {
                now->getComponent<DefaultModel>()->meshes.at(0)->textures.at(0).id = newImage4;
            } else {
                DefaultMesh::Texture ff(newImage4, "diffuse");
                now->getComponent<DefaultModel>()->meshes.at(0)->textures.push_back(ff);
            }
        }
    };
    UIRoot->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
}

void DeveloperScript::update() {
    if (keyCounter != 0) {
        keyCounter--;
        return;
    }
    if (glfwGetKey(Utility::window, GLFW_KEY_L) == GLFW_PRESS) {
        if (enable) {
            shootScript->awake();
            Input::detachOnMouseClick(&enter);
            enable = false;
            status = "Developer Mode: OFF";
            components = "";
            if (target != nullptr) {
                auto rnd = target->getComponent<Renderer>();
                if (rnd != nullptr) {
                    rnd->setSelected(false);
                }
            }
            target = nullptr;
            UIRoot->setStatus(STATUS_STOP_UPDATE | STATUS_STOP_RENDER);
        } else {
            shootScript->sleep();
            Input::attachOnMouseClick(-10, 0, 0, 0, 0, &enter, nullptr);
            enable = true;
            status = "Developer Mode: ON";
            UIRoot->setStatus(STATUS_NORMAL);
        }
        text2->setText("");
        updateText();
        keyCounter = 100;
    }
    if (target != nullptr) {
        if (glfwGetKey(Utility::window, GLFW_KEY_B) == GLFW_PRESS) {
            auto s = target->getWorldScale();
            DefaultCamera *ca = (DefaultCamera *) Runtime::getCamera();
            float a = 85 * std::min(
                    std::min(s.x, s.y), s.z
            );
            printf("%lf\n", a);
        }

        if (glfwGetKey(Utility::window, GLFW_KEY_1) == GLFW_PRESS) {
            setType = 0;
            updateState();
            keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_2) == GLFW_PRESS) {
            setType = 1;
            updateState();
            keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_3) == GLFW_PRESS) {
            setType = 2;
            updateState();
            keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_4) == GLFW_PRESS) {
            setAxis = 0;
            updateState();
            keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_5) == GLFW_PRESS) {
            setAxis = 1;
            updateState();
            keyCounter = 5;
        }
        if (glfwGetKey(Utility::window, GLFW_KEY_6) == GLFW_PRESS) {
            setAxis = 2;
            updateState();
            keyCounter = 5;
        }
        if (target && glfwGetKey(Utility::window, GLFW_KEY_7) == GLFW_PRESS) {
            adjust(len);
            updateText();
            keyCounter = 5;
        }
        if (target && glfwGetKey(Utility::window, GLFW_KEY_8) == GLFW_PRESS) {
            adjust(-len);
            updateText();
            keyCounter = 5;
        }
        if (target && glfwGetKey(Utility::window, GLFW_KEY_9) == GLFW_PRESS) {
            len += 0.1;
            updateState();
            keyCounter = 5;
        }
        if (target && glfwGetKey(Utility::window, GLFW_KEY_0) == GLFW_PRESS) {
            len -= 0.1;
            updateState();
            keyCounter = 5;
        }
    }
}

void DeveloperScript::onClickEnter() {
    if (!enable) return;
    AABBCollider *collider = AABBCollider::raycast(
            Runtime::getCamera()->getGameObject()->getWorldPosition(),
            Runtime::getCamera()->getGameObject()->getWorldForward(),
            100000.0f,
            human->getComponent<AABBCollider>()
    );
    if (target != nullptr) {
        auto rnd = target->getComponent<Renderer>();
        if (rnd != nullptr) {
            rnd->setSelected(false);
        }
        printf("Clicked!\n");
        target = nullptr;
    }
    if (collider == nullptr) {
        status = "Selected: None";
        components = "";
        updateText();
    } else {
        target = collider->getGameObject();
        status = "Selected: ";
        auto rnd = target->getComponent<Renderer>();
        if (rnd != nullptr) {
            rnd->setSelected(true);
        }
        if (target->getName() != "") status += target->getName();
        else status += " Nameless Object";
        components = "(";
        for (auto comp : target->getComponents()) {
            components += "[" + comp->getName() + "]";
        }
        components += ")";
    }
    updateText();
    updateState();
}

void DeveloperScript::updateText() {
    char buf[512];
    if (target) {
        auto pos = target->getWorldPosition();
        auto rot = target->getWorldRotation();
        auto sca = target->getWorldScale();
        sprintf(buf, "P(%0.2f, %0.2f, %0.2f) R(%0.2f, %0.2f, %0.2f) S(%0.2f, %0.2f, %0.2f)",
                pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, sca.x, sca.y, sca.z
        );
        text3->setText(buf);
    } else {
        text3->setText("");
    }
    text1->setText(status + components);
}

void DeveloperScript::updateState() {
    state = "";
    if (setType == 0) state += "Position";
    else if (setType == 1) state += "Rotation";
    else if (setType == 2) state += "Scale";
    state += ",";
    if (setAxis == 0) state += "Axis: X";
    else if (setAxis == 1) state += "Axis: Y";
    else if (setAxis == 2) state += "Axis: Z";
    state += ",Delta: " + std::to_string(len);
    text2->setText(state);
}

void DeveloperScript::adjust(float d) {
    glm::vec3 delta;
    if (setAxis == 0) delta.x = d;
    else if (setAxis == 1) delta.y = d;
    else if (setAxis == 2) delta.z = d;
    if (setType == 0) target->transform.translate(delta);
    else if (setType == 2) {
        auto dst = target->transform.getLocalScale() + delta;
        if (dst.x > 0 && dst.y > 0 && dst.z > 0)
            target->transform.setScale(dst);
    } else {
        if (setAxis == 0)target->transform.rotate(Transform::up, d);
        else if (setAxis == 1)target->transform.rotate(Transform::forward, d);
        else if (setAxis == 2)target->transform.rotate(Transform::right, d);
    }

}

DeveloperScript::DeveloperScript(UIManager *uiManager, GameObject *human, GameObject *light) {
    this->human = human;
    this->UIRoot = uiManager->getDeveloperUI();
    this->text1 = uiManager->getDevText1();
    this->text2 = uiManager->getDevText2();
    this->text3 = uiManager->getDevText3();
    this->light = light;
}
