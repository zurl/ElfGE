//
// Created by 张程易 on 06/01/2018.
//

#ifndef ELFGE_BASICOBJECT_H
#define ELFGE_BASICOBJECT_H

#include "GameEngine.h"
#include "StandardAssets.h"


namespace Prefabs {

    extern StandardMaterial material;

    class BasicObject : public Prefab {

    public:
        GameObject *instantiate(Scene *scene) override {
            auto group = scene->createGameObject("BasicObjectGroup");
            GameObject *go[6];

            go[0] = scene->createGameObject("cone.FBX")->createComponent<DefaultModel>(
                    Utility::RESOURCE_PREFIX + "Models/basic/cone.FBX");
            go[1] = scene->createGameObject("cylinder.FBX")->createComponent<DefaultModel>(
                    Utility::RESOURCE_PREFIX + "Models/basic/cylinder.FBX");
            go[2] = scene->createGameObject("pyramid.FBX")->createComponent<DefaultModel>(
                    Utility::RESOURCE_PREFIX + "Models/basic/pyramid.FBX");
            go[3] = scene->createGameObject("sphere.FBX")->createComponent<DefaultModel>(
                    Utility::RESOURCE_PREFIX + "Models/basic/sphere.FBX");
            go[4] = scene->createGameObject("teapot.FBX")->createComponent<DefaultModel>(
                    Utility::RESOURCE_PREFIX + "Models/basic/teapot.FBX");
            go[5] = scene->createGameObject("torus.FBX")->createComponent<DefaultModel>(
                    Utility::RESOURCE_PREFIX + "Models/basic/torus.FBX");

            for (int i = 0; i < 6; i++) {
                go[i]->setParent(group);
                go[i]->createComponent<AABBCollider>(true);
                go[i]->transform.setScale(glm::vec3(0.03f * i + 0.03f));
                go[i]->createComponent<Renderer>(&material,
                                                 ShaderManager::getShader("light_with_directional_shadow"));
                go[i]->transform.setPosition(glm::vec3(i * 3, 0, 0));
            }
            return group;
        }

    };
}
#endif //ELFGE_BASICOBJECT_H
