//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_DEFAULTMESH_H
#define ELFGE_DEFAULTMESH_H

#include "GameEngine.h"

class DefaultMesh: public Mesh{

public:

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;

        Vertex();

        Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoords);
    };

    struct Texture {
        unsigned int id;
        std::string type;

        Texture();

        Texture(unsigned int id, const std::string &type);
    };

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    DefaultMesh();

    DefaultMesh(aiMesh *mesh, const aiScene *scene, const std::string & directory);

    void render(Shader * shader, RenderLayer renderLayer);

    virtual ~DefaultMesh();

protected:
    void initMesh(aiMesh *mesh, const aiScene *scene);

    std::string directory;
    unsigned int VAO, VBO, EBO;
    void loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    void bindVertice();
};


#endif //ELFGE_DEFAULTMESH_H
