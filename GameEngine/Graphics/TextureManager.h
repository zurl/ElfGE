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

    static unsigned int getTextureFromFile(const std::string &path, bool gamma = false){
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
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


    static unsigned int loadTexture(const std::string & path){
        auto iter = textures.find(path);
        if( iter == textures.end() ){
            textures.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(path),
                    std::forward_as_tuple(getTextureFromFile(path))
            );
            iter = textures.find(path);
        }
        return iter->second;
    }

};


#endif //ELFGE_TEXTUREMANAGER_H
