//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_SHADERMANAGER_H
#define ELFGE_SHADERMANAGER_H

#include "Common.h"
#include "Shader.h"

class ShaderManager {
    static std::map<std::string, Shader> shaders;
public:
    static void loadShader(const std::string & name, const std::string & vertex, const std::string & fragment){
        Shader shader(vertex, fragment);
        shaders.emplace(std::piecewise_construct,
                        std::forward_as_tuple(name),
                        std::forward_as_tuple(vertex, fragment));
    }

    static Shader * getShader(const std::string & name){
        auto iter = shaders.find(name);
        if( iter == shaders.end()) throw Exception("No Shader Found");
        return &iter->second;
    }

};


#endif //ELFGE_SHADERMANAGER_H
