//
// Created by 张程易 on 12/01/2018.
//

#ifndef ELFGE_ENEMY_H
#define ELFGE_ENEMY_H

#include "StandardAssets.h"
#include "../LJK/AnimationCond.h"
#include "../LJK/EnemyCond.h"
#include "../Scripts/KeepHeight.h"

class Enemy : public Prefab {
public:
    GameObject *Human;
    Terrain *terrain;
public:
    Enemy(GameObject *Human, Terrain *terrain) : Human(Human), terrain(terrain) {}

    GameObject *instantiate(Scene *scene) override {
        static int num = 0;
        auto result = scene->createGameObject("enemy" + std::to_string(num++))
                ->createComponent<AnimatedModel>(
                        Utility::RESOURCE_PREFIX + "Models/fhe/Assets/sb.dae")
                ->createComponent<AnimationCond>()
                ->createComponent<Renderer>(
                        StandardMaterial::getInstance(),
                        ShaderManager::getShader(
                                "light_with_directional_shadow_anim")
                )
                ->createComponent<KeepHeight>(terrain)
                ->createComponent<RigidBody>()
                ->createComponent<AABBCollider>(glm::vec3(0.6f, 2.1f, 0.6f) / 2.0f,
                                                glm::vec3(0.0f, 1.0f, 0.0f), false)
                ->createComponent<EnemyCond>(5, 1, Human);
        auto enemyModel = result->getComponent<AnimatedModel>();

        enemyModel->registerAnimation("IDLE", 50, 100);
        enemyModel->registerAnimation("RUN", 325, 350);
        enemyModel->registerAnimation("DIE", 200, 215);
        enemyModel->registerAnimation("HIT", 145, 160);
        enemyModel->registerAnimation("WALK", 360, 389);
        enemyModel->playAnimation("IDLE");
        result->transform.setScale(glm::vec3(1.5));
        result->transform.translate(glm::vec3(0, 1.0f, 0));
        return result;
    }
};

#endif //ELFGE_ENEMY_H
