//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_EXCEPTION_H
#define ELFGE_EXCEPTION_H


#include <string>

class Exception {
    std::string info;
public:
    explicit Exception(const std::string &info);

    const std::string &getInfo() const;
};


#endif //ELFGE_EXCEPTION_H
