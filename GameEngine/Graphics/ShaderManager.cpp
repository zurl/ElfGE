//
// Created by 张程易 on 30/10/2017.
//

#include "ShaderManager.h"

std::map<std::string, Shader> ShaderManager::shaders;
Shader * ShaderManager::lastShader;

void ShaderManager::loadShader(const std::string &name, const std::string &vertex, const std::string &fragment,
                               const std::string &geometry) {
    auto iter = shaders.find(name);
    if( iter != shaders.end() ) return;
    shaders.emplace(std::piecewise_construct,
                    std::forward_as_tuple(name),
                    std::forward_as_tuple(vertex, fragment, geometry));
}

Shader *ShaderManager::getShader(const std::string &name) {
    auto iter = shaders.find(name);
    if( iter == shaders.end()){
        shaders.emplace(std::piecewise_construct,
                        std::forward_as_tuple(name),
                        std::forward_as_tuple(name, name));
        iter = shaders.find(name);
    }
    return &iter->second;
}

bool ShaderManager::useShader(Shader *shader) {
    bool result = shader == lastShader;
    lastShader = shader;
    return result;
}
