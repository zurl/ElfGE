//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_MESHGROUP_H
#define ELFGE_MESHGROUP_H

#include "Common.h"
#include "Core/Component.h"


class Model: public Component{
public:
    virtual void render(Shader * shader, RenderLayer renderLayer) = 0;
};

#endif //ELFGE_MESHGROUP_H
