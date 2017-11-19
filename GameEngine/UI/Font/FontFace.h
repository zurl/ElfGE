//
// Created by 张程易 on 16/11/2017.
//

#ifndef ELFGE_FONTFACE_H
#define ELFGE_FONTFACE_H

#include "Common.h"

class FontFace {
    struct Character {
        GLuint     textureID;  // 字形纹理的ID
        glm::ivec2 size;       // 字形大小
        glm::ivec2 bearing;    // 从基准线到字形左部/顶部的偏移值
        GLuint     advance;    // 原点距下一个字形原点的距离
    };
    static GLuint VAO, VBO;
    static bool isInit;
    FT_Face face;
    std::map<GLchar, Character> Characters;
    int fontSize;
public:

    int getFontSize() const;

    FontFace(FT_Library ft, const std::string & path, int fontSize = 48);

    void renderText(const std::string & text);
};


#endif //ELFGE_FONTFACE_H
