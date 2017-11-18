//
// Created by 张程易 on 16/11/2017.
//

#ifndef ELFGE_FONTMANAGER_H
#define ELFGE_FONTMANAGER_H

#include "Common.h"
#include "FontFace.h"

class FontManager {

    static FT_Library ft;

    static std::map<std::string, FontFace> fontFaces;

public:

    static void initialize();

    static FontFace * loadFont(const std::string & fontName);

};


#endif //ELFGE_FONTMANAGER_H
