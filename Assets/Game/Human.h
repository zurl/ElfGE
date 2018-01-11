//
// Created by 张程易 on 11/01/2018.
//

#ifndef ELFGE_HUMAN_H
#define ELFGE_HUMAN_H

#include "GameEngine.h"
#include "StandardAssets.h"

class Human : public Prefab{
public:
private:
    GameObject *instantiate(Scene *scene) override {

        auto human = scene->createGameObject("human")
                ->createComponent<AnimatedModel>(Utility::RESOURCE_PREFIX + "Models/elitetrooper/models/SHIT.dae")
                ->createComponent<AnimationCond>()
                ->createComponent<Renderer>(
                        &material,
                        ShaderManager::getShader("light_with_directional_shadow_anim")
                );

        return nullptr;
    }
};

#endif //ELFGE_HUMAN_H
