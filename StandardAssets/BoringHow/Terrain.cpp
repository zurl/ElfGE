//
// Created by 张程易 on 25/11/2017.
//

#include "Terrain.h"
const int size = 1024;
float nlz(float x){
    return x / 10 - 15;
}

Terrain::Terrain(const std::string &heightMapPath, const std::string &texturePath,
                 const std::vector<std::string> &textureNames) {

    heightMap = TextureManager::loadHeightMap(Utility::RESOURCE_PREFIX + "Textures/" + heightMapPath);
    vertices.reserve(size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //float add = 0;
            vertices.emplace_back(
                    glm::vec3((i) - (size / 2),
                              nlz(heightMap[(i * size + j) * 3]), (j) - (size / 2)),
                    glm::vec3(0, 1, 0), glm::vec2(i / 8.0, j / 8.0));
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
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[0]),
            "rTex"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[1]),
            "gTex"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[2]),
            "bTex"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[3]),
            "aTex"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[3]),
            "rNormal"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[4]),
            "gNormal"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[5]),
            "bNormal"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[6]),
            "aNormal"
    );
    textures.emplace_back(
            TextureManager::loadTexture2D(Utility::RESOURCE_PREFIX + "Textures/" + texturePath + textureNames[7]),
            "mix"
    );
    bindVertice();
}

Terrain::~Terrain() {
    delete heightMap;
}

void Terrain::render(Shader *shader, RenderLayer renderLayer) {
    if (renderLayer == RenderLayer::WORLD) {
        for (unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
            // 获取纹理序号（diffuse_textureN 中的 N）
            std::string name = textures[i].type;
            shader->setInt(("material." + name).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

float Terrain::getHeight(float x, float y) {
    int PosY = x + 512;
    int PosX = y + 512;
    float frac = x + 512 - PosY;
    int pos = PosY * 1024 + PosX;
    float _yA = heightMap[pos * 3] * (1 - frac) + heightMap[pos * 3 + 1024 * 3] * (frac);
    float _yB = heightMap[pos * 3 + 3] * (1 - frac) + heightMap[pos * 3 + 1025 * 3] * (frac);
    return nlz(_yA * (1 - frac) + _yB * frac); // 20.0这里是scale大小, -2.75有Translation,这里可以加参数
}

int ok = 1;
void Terrain::update() {
    if (glfwGetKey(Utility::window, GLFW_KEY_O) == GLFW_PRESS) {
        if(ok){
            ok = 0;
            getGameObject()->setStatus(STATUS_STOP_RENDER |STATUS_STOP_UPDATE);
        }
        else{
            ok = 1;
            getGameObject()->setStatus(STATUS_NORMAL);
        }
    }


    Component::update();
}
