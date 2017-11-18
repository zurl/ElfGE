//
// Created by 张程易 on 17/11/2017.
//

#ifndef ELFGE_GRAPHICSRUNTIME_H
#define ELFGE_GRAPHICSRUNTIME_H


#include <Core/Scene.h>
#include "ShadowMappingManager.h"

class GraphicsRuntime {
public:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void initialize();

    void update(Scene * scene);

};


#endif //ELFGE_GRAPHICSRUNTIME_H
