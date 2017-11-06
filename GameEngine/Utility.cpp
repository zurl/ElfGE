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
std::string Utility::ASSETS_PREFIX = "../Assets/";

int Utility::initialFreeType() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, (Utility::ASSETS_PREFIX + "Resources/Fonts/arial.ttf").c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

    return 0;
}

int Utility::__initialOpenGL() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME.c_str(), NULL, NULL);
    //glfwSetInputMode(__glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    return 0;
}

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

void Utility::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    SCREEN_HEIGHT = height;
    SCREEN_WIDTH = width;
}
