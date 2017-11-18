//
// Created by 张程易 on 16/11/2017.
//

#include <Core/Utility.h>
#include "FontManager.h"
std::map<std::string, FontFace> FontManager::fontFaces;
FT_Library FontManager::ft;


void FontManager::initialize() {
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        exit(1);
    }
}

FontFace * FontManager::loadFont(const std::string &fontName) {
    auto iter = fontFaces.find(fontName);
    if(iter == fontFaces.end()){
        fontFaces.emplace(std::piecewise_construct,
                          std::forward_as_tuple(fontName),
                          std::forward_as_tuple(ft, Utility::RESOURCE_PREFIX + "Fonts/" + fontName + ".ttf"));
        iter = fontFaces.find(fontName);
    }
    return &iter->second;
}
