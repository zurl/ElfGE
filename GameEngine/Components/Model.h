//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_MESHGROUP_H
#define ELFGE_MESHGROUP_H

#include "../Common.h"
#include "Mesh.h"
#include "Component.h"


class Model: public Component{
public:
    virtual void __render(Shader * shader) = 0;

    void start() override;

    void update() override;
};


#endif //ELFGE_MESHGROUP_H
