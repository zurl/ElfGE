//
// Created by lulufa on 2018/1/11.
//

#include "EnemyScript.h"


void EnemyScript::start() {


    enemyGroup = new GameObject("enemygroup");
    enemyGroup->setParent(getGameObject());
    //enemy one
    auto enemy = enemyFactory.instantiate(Runtime::getScene());
    enemy->start();
    enemy->transform.translate(glm::vec3(3, 1, 0));
    enemy->setParent(enemyGroup);

    //enemy two
    auto enemy2 = enemyFactory.instantiate(Runtime::getScene());
    enemy->start();
    enemy2->transform.translate(glm::vec3(20, 1, 0));
    enemy2->setParent(enemyGroup);


}

void EnemyScript::update() {

    for(GameObject * e : enemyGroup->getChildren()){
        e->getComponent<EnemyCond>()->move();
    }

}