//
// Created by lulufa on 2018/1/12.
//

#ifndef ELFGE_BOOM_H
#define ELFGE_BOOM_H

#include "StandardAssets.h"
#include "GameEngine.h"
#include "UI/UI.h"
#include "../Prefab/PlainText.h"
#include "../Prefabs.h"
#include "../Game/UIManager.h"
#include "EnemyScript.h"

using namespace Prefabs;

class BoomScript : public GameScript {
public:
    GameObject *boomCube;
    GameObject *Enemy;
    GameObject *Human;
    GameObject *pfobj;
    ParticleFactory *pf;

    Text *text;
    int BoomCnt;

    BoomScript(GameObject *enemy, GameObject *human, Text *text) : Enemy(enemy), Human(human), text(text) {}

    void start() override {
        boomCube = instantiate<Bomb>(glm::vec3(10000.0f, 0.0f, 0.0f));
        pfobj = new GameObject("pf");
        pfobj->createComponent<ParticleFactory>();
        pfobj->setParent(getGameObject());
        pfobj->start();
        pf = pfobj->getComponent<ParticleFactory>();


    }

    void update() override {
        if (glfwGetKey(Utility::window, GLFW_KEY_E) == GLFW_PRESS) {
            printf("Set Boom!");
            BoomCnt = 300;
            boomCube->transform.setPosition(
                    Human->getWorldPosition() + Human->getWorldForward() * 3.0f + glm::vec3(0, 0, 0));
        }

        if (BoomCnt > 0) {
            BoomCnt--;
            if (BoomCnt == 0) {
                printf("in\n");
                for (GameObject *e : Enemy->getComponent<EnemyScript>()->enemyGroup->getChildren()) {
                    printf("One monster!\n");
                    glm::vec3 disVec = e->getWorldPosition() - boomCube->getWorldPosition();
                    float dis = disVec.x * disVec.x + disVec.y * disVec.y + disVec.z * disVec.z;
                    if (dis < 10) {
                        e->getComponent<EnemyCond>()->Health -= 10;
                    }
                }

                pfobj->transform.setPosition(boomCube->getWorldPosition() + glm::vec3(0.0f, 0.5f, 0.0f));
                pf->addExplosion();
                boomCube->transform.setPosition(glm::vec3(10000.0, 0, 0));
                text->setText("");
            } else if (BoomCnt <= 100) {
                text->setText("1");
            } else if (BoomCnt <= 200) {
                text->setText("2");
            } else if (BoomCnt <= 300) {
                text->setText("3");
            } else if (BoomCnt <= 400) {
                text->setText("4");
            } else if (BoomCnt <= 500) {
                text->setText("5");
            }
        }
    }

};

#endif //ELFGE_BOOM_H
