//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_COMPONENT_H
#define ELFGE_COMPONENT_H


#include "GameObject.h"

class Component {
    GameObject * parent;
public:
    virtual void update() = 0;

    GameObject *getParent() const;

    void __setParent(GameObject *parent);
};


#endif //ELFGE_COMPONENT_H
