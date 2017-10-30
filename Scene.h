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
    GameObject * rootGameObject;
public:
    Scene();
    virtual void start(){
        rootGameObject->start();
    }
    virtual void update(){
        rootGameObject->update();
    }
    virtual ~Scene();
    Camera *getCamera() const;
    void setCamera(Camera *camera);
    void addGameObject(GameObject * gameObject);
    GameObject * createGameObject();


};


#endif //ELFGE_SCENE_H
