//
// Created by lulufa on 2018/1/11.
//

#include "EnemyScript.h"


float EnemyScript::myrand(float min, float max){
    float seed = rand() * 1.0f / RAND_MAX; // 0-1
    return min + seed * (max - min);
}


void EnemyScript::start() {

    enemyGroup = new GameObject("enemygroup");
    enemyGroup->setParent(getGameObject());


//    //enemy one
//    auto enemy = enemyFactory.instantiate(Runtime::getScene());
//    enemy->start();
//    enemy->transform.translate(glm::vec3(3, 1, 0));
//    enemy->setParent(enemyGroup);
//
//    //enemy two
//    auto enemy2 = enemyFactory.instantiate(Runtime::getScene());
//    enemy->start();
//    enemy2->transform.translate(glm::vec3(20, 1, 0));
//    enemy2->setParent(enemyGroup);

    for(int i = 0; i < 5; i ++) {
        float x = myrand(-50, 50);
        float z = myrand(-50, 50);
        float y = enemyFactory.terrain->getHeight(x, z);
        auto enemy2 = enemyFactory.instantiate(Runtime::getScene());
        enemy2->start();
        enemy2->setParent(enemyGroup);
        enemy2->transform.setPosition(glm::vec3(x, y, z));
    }


}

void EnemyScript::update() {
    for(GameObject * e : enemyGroup->getChildren()){
        e->getComponent<EnemyCond>()->move();
    }

}