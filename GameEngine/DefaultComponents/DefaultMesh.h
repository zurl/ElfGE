//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_DEFAULTMESH_H
#define ELFGE_DEFAULTMESH_H

#include "../Common.h"
#include "../Components/Mesh.h"

class DefaultMesh: public Mesh{

public:

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        //glm::vec3 tangent;
        //glm::vec3 bitangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    DefaultMesh();

    DefaultMesh(aiMesh *mesh, const aiScene *scene, const std::string & directory);

    void render(Shader * shader);

    virtual ~DefaultMesh();

protected:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    std::string directory;
    unsigned int VAO, VBO, EBO;

    void loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    void bindVertice();
};


#endif //ELFGE_DEFAULTMESH_H
