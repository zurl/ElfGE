//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_COMPONENT_H
#define ELFGE_COMPONENT_H

#include <Common.h>

class GameObject;

class Component {
    GameObject *gameObject;

    void setGameObject(GameObject *parent);

    friend class GameObject;

public:

    virtual std::string getName();

    virtual void start();

    virtual void update();

    virtual void destroy();

    virtual void sleep();

    virtual void awake();

    virtual void updateGraphics(RenderLayer renderLayer);

    GameObject *getGameObject() const;

    virtual ~Component();
};


#endif //ELFGE_COMPONENT_H