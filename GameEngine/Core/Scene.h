//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_SCENE_H
#define ELFGE_SCENE_H

#include <Graphics/ShadowMappingManager.h>
#include "../Common.h"
#include "Camera.h"
#include "GameObject.h"
#include "Graphics/ShaderManager.h"

class Scene {
    ShadowMappingManager * shadowMappingManager;
    Camera * camera;
    GameObject * rootGameObject;
public:
    Scene();
    virtual void start();
    virtual void update();
    virtual void destroy();
    virtual void updateGraphics(RenderLayer renderLayer);
    virtual ~Scene();
    Camera *getCamera() const;
    void setCamera(Camera *camera);

    ShadowMappingManager *getShadowMappingManager() const;

    void setShadowMappingManager(ShadowMappingManager *shadowMappingManager);

    void addGameObject(GameObject * gameObject);
    GameObject * createGameObject();
};


#endif //ELFGE_SCENE_H
