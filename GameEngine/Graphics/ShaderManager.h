//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_SHADERMANAGER_H
#define ELFGE_SHADERMANAGER_H

#include "Common.h"
#include "Shader.h"

class ShaderManager {
    static std::map<std::string, Shader> shaders;

    static Shader * lastShader;
public:
    static void loadShader(const std::string & name, const std::string & vertex, const std::string & fragment, const std::string & geometry = "");

    static Shader * getShader(const std::string & name);

    static bool useShader(Shader * shader);

};


#endif //ELFGE_SHADERMANAGER_H
