//
// Created by 张程易 on 12/01/2018.
//

#ifndef ELFGE_LIGHT_H
#define ELFGE_LIGHT_H

#include <ShadowMapping/DirectionalShadowMappingManager.h>
#include "GameEngine.h"
#include "../Scripts/FollowHuman.h"

class LandLight: public Prefab{
    GameObject * human;
public:
    LandLight(GameObject *human) : human(human) {}
    GameObject *instantiate(Scene *scene) override {
        auto light = scene->createGameObject("light")
                ->createComponent<DirectLighting>(
                        glm::vec3(0.2f, 0.2f, 0.2f),
                        glm::vec3(0.2f, 0.2f, 0.2f),
                        glm::vec3(0.2f, 0.2f, 0.2f)
                );
        light->transform.setRotation(glm::vec3(0, 0, 60));
        light->createComponent<FollowHuman>(human, glm::vec3(2, 5, 2));
        scene->setShadowMappingManager(new DirectionalShadowMappingManager(light->getComponent<DirectLighting>()));
        scene->getShadowMappingManager()->initialize();
        return light;
    }
};

#endif //ELFGE_LIGHT_H