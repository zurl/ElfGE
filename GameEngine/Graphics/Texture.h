//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_TEXTURE_H
#define ELFGE_TEXTURE_H

#include "Common.h"

struct Texture{
    unsigned int id;
    std::string type;
    Texture(unsigned int id, const std::string &type) : id(id), type(type) {}
};

#endif //ELFGE_TEXTURE_H
