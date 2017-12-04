//
// Created by sky on 2017/12/4.
//

#include "SphereMesh.h"
static unsigned int indices_array_sphere[] = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        8, 9, 10,
        10, 11, 8,
        12, 13, 14,
        14, 15, 12,
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
};

static float vertices_array[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
};
SphereMesh::SphereMesh(){
    Vertex vertex;
    for(int i = 0; i < 6; i++){
        Vertex v[4];
        for(int j = 0; j < 4; j ++){
            int k = i * 4 + j;
            vertex.position = glm::vec3(vertices_array[8 * k], vertices_array[8 * k + 1], vertices_array[8 * k + 2]);
            vertex.normal = glm::vec3(vertices_array[8 * k + 3], vertices_array[8 * k + 4],vertices_array[8 * k + 5]);
            vertex.texCoords = glm::vec2(vertices_array[8 * k + 6], vertices_array[8 * k + 7]);
            v[j] = vertex;
        }
        glm::vec3 tangent1, bitangent1;
        computeTangent(tangent1, bitangent1, v[0], v[1], v[2]);
        for(int j = 0; j < 4; j ++){
            v[j].tangent = tangent1;
            v[j].bitangent = bitangent1;
            vertices.emplace_back(v[j]);
        }
    }
    for(int i = 0; i < 36;i ++) {
        indices.push_back(indices_array_sphere[i]);
    }

    bindVertice();
}

SphereMesh::SphereMesh(const std::string specularName,
                   const std::string diffuseName,
                   const std::string normalName
) :SphereMesh(){
    Texture specular, diffuse, normal;
    if(specularName != ""){
        diffuse.id = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/" + diffuseName
        );
        specular.type = "specular";
        textures.emplace_back(specular);
    }

    if(diffuseName!= ""){
        specular.id = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/" + specularName
        );
        diffuse.type = "diffuse";
        textures.emplace_back(diffuse);
    }
    if( normalName != ""){
        normal.id = TextureManager::loadTexture2D(
                Utility::RESOURCE_PREFIX + "Textures/" + normalName
        );
        normal.type = "normal";
        textures.emplace_back(normal);
    }
}
