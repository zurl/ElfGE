//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_UTILITY_H
#define ELFGE_UTILITY_H

#include "Common.h"

class Utility {
public:
    static const std::string ASSETS_PREFIX = ".";

    static const char * readFile(const char * filePath){
        FILE * fp = fopen(fileName, "r");
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
    static unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false){
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data){
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else{
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }


};


#endif //ELFGE_UTILITY_H
