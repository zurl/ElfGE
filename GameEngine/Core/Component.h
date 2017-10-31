//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_COMPONENT_H
#define ELFGE_COMPONENT_H

class GameObject;

class Component {
    GameObject * gameObject;

    void setGameObject(GameObject *parent);

    friend class GameObject;

public:
    virtual void start() = 0;

    virtual void update() = 0;

    virtual void destroy() = 0;

    GameObject * getGameObject() const;

    virtual ~Component();
};


#endif //ELFGE_COMPONENT_H
