//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_LIGHTINGMANAGER_H
#define ELFGE_LIGHTINGMANAGER_H

#include "Common.h"
#include "Graphics/Components/Lighting.h"

class LightingManager {
    static std::map<std::string, std::list<Lighting *>> lightings;
public:
    static void attachLighting(const std::string &name, Lighting *lighting) {
        auto iter = lightings.find(name);
        if (iter == lightings.end()) {
            lightings.emplace(std::piecewise_construct,
                              std::forward_as_tuple(name),
                              std::forward_as_tuple()
            );
            iter = lightings.find(name);
        }
        iter->second.emplace_back(lighting);
    }

    static void detachLighting(const std::string &name, Lighting *lighting) {
        auto iter = lightings.find(name);
        if (iter == lightings.end()) {
            throw Exception("No Such Lighting");
        }
        iter->second.remove(lighting);
    }

    static void update(Shader *shader) {
        char buffer[128];
        for (auto &x : lightings) {
            int i = 0;
            for (auto &y: x.second) {
                sprintf(buffer, "%s[%d].", x.first.c_str(), i++);
                y->update(buffer, shader);
            }
        }
    }
};


#endif //ELFGE_LIGHTINGMANAGER_H
