//
// Created by 张程易 on 11/01/2018.
//

#ifndef ELFGE_HUMAN_H
#define ELFGE_HUMAN_H

#include "GameEngine.h"
#include "StandardAssets.h"
#include "../LJK/AnimationCond.h"
#include "../Scripts/KeepHeight.h"

class Human : public Prefab {
    std::string path;
    Terrain * terrain;

public:
    Human(const std::string &path, Terrain *terrain) : path(path), terrain(terrain) {}

    GameObject *instantiate(Scene *scene) override {
        Config::Hack = 1;

        auto human = scene->createGameObject("human")
                ->createComponent<AnimatedModel>(path)
                ->createComponent<AnimationCond>()
                ->createComponent<Renderer>(
                        StandardMaterial::getInstance(),
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                );

        auto realHuman = scene->createGameObject("realHuman")
                ->createComponent<KeepHeight>(terrain)
                ->createComponent<CharacterController>(human, 0.002f, 0.3)
                ->createComponent<RigidBody>()
                ->createComponent<AABBCollider>(glm::vec3(0.6f, 2.1f, 0.6f) / 2.0f,
                                                glm::vec3(0.0f, 1.0f, 0.0f), false);

        realHuman->transform.translate(glm::vec3(3, 1, 0));
        human->setParent(realHuman);

        auto humanModel = human->getComponent<AnimatedModel>();
        humanModel->registerAnimation("IDLE", 60, 90);
        humanModel->registerAnimation("RUN", 600, 614);
        humanModel->registerAnimation("JUMP", 301, 313);
        humanModel->registerAnimation("SHOOT", 375, 460);
        humanModel->registerAnimation("DOWN", 330, 350);
        humanModel->registerAnimation("RUN_DOWN", 471, 488);
        humanModel->registerAnimation("DIE", 685, 705);

        human->transform.rotate(glm::vec3(0, 1, 0), glm::half_pi<float>());

        human->getComponent<AnimationCond>()->play(1);
        human->getComponent<AnimationCond>()->play(0);

        Config::Hack = 0;
        return human;
    }
};

#endif //ELFGE_HUMAN_H
