//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_SCENE_H
#define ELFGE_SCENE_H

#include "Common.h"
#include "Camera.h"
#include "GameObject.h"

class Scene {
    Camera * camera;
    std::list<GameObject *> gameObjectList;


};


#endif //ELFGE_SCENE_H
