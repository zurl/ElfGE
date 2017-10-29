//
// Created by 张程易 on 29/10/2017.
//

#include "Exception.h"

Exception::Exception(const std::string &info) : info(info) {}

const std::string &Exception::getInfo() const {
    return info;
}
