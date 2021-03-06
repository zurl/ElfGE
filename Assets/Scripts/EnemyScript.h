//
// Created by lulufa on 2018/1/11.
//

#ifndef ELFGE_ENEMYSCRIPT_H
#define ELFGE_ENEMYSCRIPT_H


#include "StandardAssets.h"
#include "GameEngine.h"
#include "UI/UI.h"
#include "../Prefab/PlainText.h"
#include "../Prefabs.h"
#include "../LJK/EnemyCond.h"
#include "../Game/Enemy.h"

using namespace Prefabs;

class EnemyScript : public GameScript{
public:
    GameObject * enemyGroup;
    GameObject * Human;
    Enemy enemyFactory;

public:
    EnemyScript(GameObject * human, Terrain * terrain) : Human(human), enemyFactory(human, terrain){}

    float myrand(float min, float max);
    void start() override;
    void update() override;
};


#endif //ELFGE_ENEMYSCRIPT_H
