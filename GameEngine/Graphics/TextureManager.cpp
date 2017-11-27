//
// Created by 张程易 on 31/10/2017.
//

#include "TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <gli/gli.hpp>
std::map<std::string, unsigned int> TextureManager::textures;

unsigned int TextureManager::loadTexture2D(const std::string &path) {
    auto iter = textures.find(path);
    if( iter == textures.end() ){
        textures.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(path),
                std::forward_as_tuple(getTexture2DFromFile(path))
        );
        iter = textures.find(path);
    }
    return iter->second;
}

unsigned int TextureManager::loadTexture3D(const std::vector<std::string> &faces) {
    auto iter = textures.find(faces[0]);
    if( iter == textures.end() ){
        textures.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(faces[0]),
                std::forward_as_tuple(getTexture3DFromFile(faces))
        );
        iter = textures.find(faces[0]);
    }
    return iter->second;
}
unsigned int TextureManager::getTexture2DFromFile(const std::string &path, bool gamma) {
    if( strstr(path.c_str(), ".DDS") != NULL) return getDDSTexture(path);

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
unsigned int TextureManager::getDDSTexture(const std::string &path) {
    gli::texture Texture = gli::load(path.c_str());
    if(Texture.empty())
        return 0;

    gli::gl GL(gli::gl::PROFILE_GL33);
    gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
    GLenum Target = GL.translate(Texture.target());

    GLuint TextureName = 0;
    glGenTextures(1, &TextureName);
    glBindTexture(Target, TextureName);
    glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
    glTexParameteri(Target, GL_TEXTURE_SWIZZLE_R, Format.Swizzles[0]);
    glTexParameteri(Target, GL_TEXTURE_SWIZZLE_G, Format.Swizzles[1]);
    glTexParameteri(Target, GL_TEXTURE_SWIZZLE_B, Format.Swizzles[2]);
    glTexParameteri(Target, GL_TEXTURE_SWIZZLE_A, Format.Swizzles[3]);

    glm::tvec3<GLsizei> const Extent(Texture.extent());
    GLsizei const FaceTotal = static_cast<GLsizei>(Texture.layers() * Texture.faces());

    switch(Texture.target())
    {
        case gli::TARGET_1D:
            glTexStorage1D(
                    Target, static_cast<GLint>(Texture.levels()), Format.Internal, Extent.x);
            break;
        case gli::TARGET_1D_ARRAY:
        case gli::TARGET_2D:
        case gli::TARGET_CUBE:
            glTexStorage2D(
                    Target, static_cast<GLint>(Texture.levels()), Format.Internal,
                    Extent.x, Texture.target() == gli::TARGET_2D ? Extent.y : FaceTotal);
            break;
        case gli::TARGET_2D_ARRAY:
        case gli::TARGET_3D:
        case gli::TARGET_CUBE_ARRAY:
            glTexStorage3D(
                    Target, static_cast<GLint>(Texture.levels()), Format.Internal,
                    Extent.x, Extent.y,
                    Texture.target() == gli::TARGET_3D ? Extent.z : FaceTotal);
            break;
        default:
            assert(0);
            break;
    }

    for(std::size_t Layer = 0; Layer < Texture.layers(); ++Layer)
        for(std::size_t Face = 0; Face < Texture.faces(); ++Face)
            for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
            {
                GLsizei const LayerGL = static_cast<GLsizei>(Layer);
                glm::tvec3<GLsizei> Extent(Texture.extent(Level));
                Target = gli::is_target_cube(Texture.target())
                         ? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Face)
                         : Target;

                switch(Texture.target())
                {
                    case gli::TARGET_1D:
                        if(gli::is_compressed(Texture.format()))
                            glCompressedTexSubImage1D(
                                    Target, static_cast<GLint>(Level), 0, Extent.x,
                                    Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
                                    Texture.data(Layer, Face, Level));
                        else
                            glTexSubImage1D(
                                    Target, static_cast<GLint>(Level), 0, Extent.x,
                                    Format.External, Format.Type,
                                    Texture.data(Layer, Face, Level));
                        break;
                    case gli::TARGET_1D_ARRAY:
                    case gli::TARGET_2D:
                    case gli::TARGET_CUBE:
                        if(gli::is_compressed(Texture.format()))
                            glCompressedTexSubImage2D(
                                    Target, static_cast<GLint>(Level),
                                    0, 0,
                                    Extent.x,
                                    Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Extent.y,
                                    Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
                                    Texture.data(Layer, Face, Level));
                        else
                            glTexSubImage2D(
                                    Target, static_cast<GLint>(Level),
                                    0, 0,
                                    Extent.x,
                                    Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Extent.y,
                                    Format.External, Format.Type,
                                    Texture.data(Layer, Face, Level));
                        break;
                    case gli::TARGET_2D_ARRAY:
                    case gli::TARGET_3D:
                    case gli::TARGET_CUBE_ARRAY:
                        if(gli::is_compressed(Texture.format()))
                            glCompressedTexSubImage3D(
                                    Target, static_cast<GLint>(Level),
                                    0, 0, 0,
                                    Extent.x, Extent.y,
                                    Texture.target() == gli::TARGET_3D ? Extent.z : LayerGL,
                                    Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
                                    Texture.data(Layer, Face, Level));
                        else
                            glTexSubImage3D(
                                    Target, static_cast<GLint>(Level),
                                    0, 0, 0,
                                    Extent.x, Extent.y,
                                    Texture.target() == gli::TARGET_3D ? Extent.z : LayerGL,
                                    Format.External, Format.Type,
                                    Texture.data(Layer, Face, Level));
                        break;
                    default: assert(0); break;
                }
            }
    return TextureName;
}

unsigned int TextureManager::getTexture3DFromFile(const std::vector<std::string> &faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

unsigned char *TextureManager::loadHeightMap(const std::string &path) {
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    return data;
}