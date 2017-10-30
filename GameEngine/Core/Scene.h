//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_SCENE_H
#define ELFGE_SCENE_H

#include "../Common.h"
#include "../Components/Camera.h"
#include "GameObject.h"
#include "../Shader/ShaderManager.h"

class Scene {
    Camera * camera;
    GameObject * rootGameObject;
public:
    Scene();
    virtual void start();
    virtual void update();
    virtual void destroy();
    virtual ~Scene();
    Camera *getCamera() const;
    void setCamera(Camera *camera);
    void addGameObject(GameObject * gameObject);
    GameObject * createGameObject();
};


#endif //ELFGE_SCENE_H
