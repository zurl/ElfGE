//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_COMMON_H
#define ELFGE_COMMON_H

#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <functional>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>


#ifdef _linux
#include <glad.h>
#else
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#endif

#include "Exception.h"
#include <ft2build.h>
#include FT_FREETYPE_H

enum class RenderLayer {
    WORLD_SHADOW,
    WORLD,
    SCREEN
};

const int STATUS_NORMAL = 0;
const int STATUS_STOP_RENDER = 1;
const int STATUS_STOP_UPDATE = 2;


#endif //ELFGE_COMMON_H
