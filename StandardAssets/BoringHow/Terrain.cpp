//
// Created by 张程易 on 25/11/2017.
//

#include "Terrain.h"

Terrain::Terrain(const std::string &heightMapPath, const std::string &texturePath, const std::string &normalPath) {
    const int size = 1024;
    heightMap = TextureManager::loadHeightMap(Utility::RESOURCE_PREFIX + "Textures/" + heightMapPath);
    vertices.reserve(size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float add = 0;
            vertices.emplace_back(
                    glm::vec3((i) - (size / 2),
                              heightMap[(i * size + j) * 3] / 100.0, (j) - (size / 2)),
                    glm::vec3(0, 1, 0),
                    glm::vec2(i / 8.0 + add / 2.0, j / 8.0 + add / 10.0));
        }
    }
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            glm::vec3 nTmp = {0, 0, 0};
            nTmp += glm::cross(vertices[i * size + j].position - vertices[i * size + j + size].position,
                               vertices[i * size + j].position - vertices[i * size + j - 1].position);
            nTmp += glm::cross(vertices[i * size + j].position - vertices[i * size + j - 1].position,
                               vertices[i * size + j].position - vertices[i * size + j - size].position);
            nTmp += glm::cross(vertices[i * size + j].position - vertices[i * size + j - size].position,
                               vertices[i * size + j].position - vertices[i * size + j + 1].position);
            nTmp += glm::cross(vertices[i * size + j].position - vertices[i * size + j + 1].position,
                               vertices[i * size + j].position - vertices[i * size + j + size].position);
            nTmp = glm::normalize(nTmp);
            if (nTmp.y < 0) nTmp = -nTmp;
            vertices[i * size + j].normal = nTmp;
        }
    }
    indices.reserve((size - 1) * (size - 1) * 6);
    for (unsigned int i = 0; i < size - 1; i++) {
        for (unsigned int j = 0; j < size - 1; j++) {
            glm::vec3 tangent1, bitangent1;
            computeTangent(tangent1, bitangent1,
                           vertices[i * size + j],
                           vertices[i * size + j + 1],
                           vertices[i * size + j + size]);
            vertices[i * size + j].tangent = tangent1;
            vertices[i * size + j + 1].tangent = tangent1;
            vertices[i * size + j + size].tangent = tangent1;
            vertices[i * size + j].bitangent = bitangent1;
            vertices[i * size + j + 1].bitangent = bitangent1;
            vertices[i * size + j + size].bitangent = bitangent1;

            computeTangent(tangent1, bitangent1,
                           vertices[i * size + j + size],
                           vertices[i * size + j + 1],
                           vertices[i * size + j + size + 1]);
            vertices[i * size + j + size].tangent = tangent1;
            vertices[i * size + j + 1].tangent = tangent1;
            vertices[i * size + j + size + 1].tangent = tangent1;
            vertices[i * size + j + size].bitangent = bitangent1;
            vertices[i * size + j + 1].bitangent = bitangent1;
            vertices[i * size + j + size + 1].bitangent = bitangent1;

            indices.emplace_back(i * size + j);
            indices.emplace_back(i * size + j + 1);
            indices.emplace_back(i * size + j + size);
            indices.emplace_back(i * size + j + size);
            indices.emplace_back(i * size + j + 1);
            indices.emplace_back(i * size + j + size + 1);
        }
    }
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath),
            "diffuse"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath),
            "specular"
    );
    if (normalPath != "") {
        textures.emplace_back(
                TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + normalPath),
                "normal"
        );
    }
    bindVertice();
}

Terrain::~Terrain() {
    delete heightMap;
}
