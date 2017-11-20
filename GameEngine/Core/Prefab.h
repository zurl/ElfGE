//
// Created by 张程易 on 20/11/2017.
//

#ifndef ELFGE_PREFAB_H
#define ELFGE_PREFAB_H

class Scene;
class GameObject;

class Prefab {
    virtual GameObject * instantiate(Scene * scene) = 0;
};

#endif //ELFGE_PREFAB_H
