//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_UTILITY_H
#define ELFGE_UTILITY_H

#include "Common.h"

class Utility {
public:

    static GLFWwindow* window;

    static std::string WINDOW_NAME;
    static std::string RESOURCE_PREFIX;

    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    static double deltaTime;

    static const char * getTextFromFile(const char * filePath);

};


#endif //ELFGE_UTILITY_H
