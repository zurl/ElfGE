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
                        glm::vec3(0.5f, 0.5f, 0.5f),
                        glm::vec3(0.8f, 0.8f, 0.8f),
                        glm::vec3(0.4f, 0.4f, 0.4f)
                );
        light->transform.setRotation(glm::vec3(0, 0, 60));
            glm::vec3 frd = light->getWorldForward();
            printf("%f %f %f\n", frd.x, frd.y, frd.z);
//            exit(0);
        light->createComponent<FollowHuman>(human);
        scene->setShadowMappingManager(new DirectionalShadowMappingManager(
                light->getComponent<DirectLighting>(), Config::ShadowResolution
        ));
        scene->getShadowMappingManager()->initialize();
        return light;
    }
};

#endif //ELFGE_LIGHT_H
