//
// Created by sky on 2017/12/4.
//
//
// Created by sky on 2017/12/4.
//

#include "PlaneMesh.h"
static unsigned int indices_array_plane[] = {
        0, 1, 2,
        2, 3, 1,
};

static float vertices_array[] = {
        // positions          // normals           // texture coords
        -1.0f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  0.0f, 0.0f,
        -1.0f, 0.0f, 1.0f,  0.0f,  1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
};
PlaneMesh::PlaneMesh(){
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
        indices.push_back(indices_array_plane[i]);
    }

    bindVertice();
}

PlaneMesh::PlaneMesh(const std::string specularName,
                       const std::string diffuseName,
                       const std::string normalName
) :PlaneMesh(){
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

