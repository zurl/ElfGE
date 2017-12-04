//
// Created by 张程易 on 31/10/2017.
//

#ifndef ELFGE_TEXTUREMANAGER_H
#define ELFGE_TEXTUREMANAGER_H


#include "Texture.h"
#include "Common.h"
#include "Core/Utility.h"

class TextureManager {
    static std::map<std::string, unsigned int> textures;
public:

    static unsigned int getDDSTexture(const std::string &path);

    static unsigned char* loadHeightMap(const std::string &path);

    static unsigned int getTexture3DFromFile(const std::vector<std::string> & faces);

    static unsigned int getTexture2DFromFile(const std::string &path, bool gamma = false);

    static unsigned int loadTexture2D(const std::string & path) ;

    static unsigned int loadTexture3D(const std::vector<std::string> & faces);

};


#endif //ELFGE_TEXTUREMANAGER_H
