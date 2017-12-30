//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_LIGHTING_H
#define ELFGE_LIGHTING_H


#include "Graphics/Shader.h"
#include "Core/Component.h"

class Lighting : public Component {
public:

    virtual std::string getName() = 0;

    void start() override;

    void update() override;

    void destroy() override;

    virtual void update(const std::string &prefix, Shader *shader) = 0;

};


#endif //ELFGE_LIGHTING_H
