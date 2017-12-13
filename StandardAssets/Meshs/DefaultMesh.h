//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_DEFAULTMESH_H
#define ELFGE_DEFAULTMESH_H

#include "GameEngine.h"

class DefaultMesh : public Mesh {

public:

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 bitangent;

        Vertex();

        Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoords);
    };


    static inline void computeTangent(
            glm::vec3 &tangent1, glm::vec3 &bitangent1,
            Vertex &v0, Vertex &v1, Vertex v2
    ) {
        glm::vec3 nm(0.0, 0.0, 1.0);
        glm::vec3 edge1 = v1.position - v0.position;
        glm::vec3 edge2 = v2.position - v0.position;
        glm::vec2 deltaUV1 = v1.texCoords - v0.texCoords;
        glm::vec2 deltaUV2 = v2.texCoords - v0.texCoords;
        GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangent1 = glm::normalize(tangent1);

        bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        bitangent1 = glm::normalize(bitangent1);
    }

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

    DefaultMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory);

    void render(Shader *shader, RenderLayer renderLayer);

    virtual ~DefaultMesh();

protected:
    void initMesh(aiMesh *mesh, const aiScene *scene);

    std::string directory;
    unsigned int VAO, VBO, EBO;

    void loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    void bindVertice();
};


#endif //ELFGE_DEFAULTMESH_H
