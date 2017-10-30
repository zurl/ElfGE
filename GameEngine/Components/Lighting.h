//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_LIGHTING_H
#define ELFGE_LIGHTING_H


#include "../Shader/Shader.h"
#include "Component.h"
#include "../Shader/LightingManager.h"

class Lighting: public Component {
public:

    virtual std::string getName() = 0;

    virtual void update(const std::string &prefix, Shader * shader) = 0;

    void start() override;

    void update() override;

    virtual ~Lighting();
};


#endif //ELFGE_LIGHTING_H
