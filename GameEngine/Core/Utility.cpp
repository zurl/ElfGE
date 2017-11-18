//
// Created by 张程易 on 29/10/2017.
//

#define STB_IMAGE_IMPLEMENTATION

#include "Utility.h"


int Utility::SCREEN_WIDTH = 1024;
int Utility::SCREEN_HEIGHT = 768;
double Utility::deltaTime = 0.0;
GLFWwindow* Utility::window = nullptr;

std::string Utility::WINDOW_NAME = "ElfGameEngine";
std::string Utility::RESOURCE_PREFIX = "../Resources/";


const char *Utility::getTextFromFile(const char *filePath) {
    FILE * fp = fopen(filePath, "r");
    if( fp == nullptr ) return nullptr;
    fseek(fp, 0L, SEEK_END);
    long flen = ftell(fp);
    char * result = (char *)malloc((size_t)flen);
    fseek(fp, 0L, SEEK_SET);
    char * now = result; int c;
    while((c = fgetc(fp))!= EOF) *now++ = (char) c;
    *now = 0;
    return result;
}
