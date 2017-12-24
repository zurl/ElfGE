//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_SCENE_H
#define ELFGE_SCENE_H

#include <Graphics/ShadowMappingManager.h>
#include "Common.h"
#include "GameObject.h"
#include "Graphics/ShaderManager.h"

class Camera;

class Scene {
    ShadowMappingManager *shadowMappingManager = nullptr;
    Camera *camera;
    GameObject *rootGameObject;
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

    void addGameObject(GameObject *gameObject);

    GameObject *createGameObject(const std::string & name = "");

protected:
    template<typename T, typename... Args>
    GameObject *set(Args &&... args) {
        auto prefab = new T(std::forward<Args>(args)...);
        auto result = prefab->instantiate(this);
        delete prefab;
        return result;
    }

};


#endif //ELFGE_SCENE_H
