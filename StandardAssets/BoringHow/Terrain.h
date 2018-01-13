//
// Created by 张程易 on 25/11/2017.
//

#ifndef ELFGE_TERRAINMESH_H
#define ELFGE_TERRAINMESH_H


#include <Meshs/DefaultMesh.h>

class Terrain : public DefaultMesh {
    unsigned char *heightMap;
public:
    Terrain(const std::string &heightMapPath,
            const std::string &texturePath,
            const std::vector<std::string> &textureNames
           );

    glm::vec3 getNormal(float x, float y) {
        int PosY = x + 512;
        int PosX = y + 512;
        float frac = x + 512 - PosY;
        int pos = PosY * 1024 + PosX;
        glm::vec3 _yA = vertices[pos].normal * (1 - frac) + vertices[pos + 1024].normal * (frac);
        glm::vec3 _yB = vertices[pos + 1].normal * (1 - frac) + vertices[pos + 1025].normal * (frac);
        frac = y + 512 - PosX;
        //hero->position.y = -2.75 + _yA * (1-frac) + _yB * frac;
        return (_yA * (1 - frac) + _yB * frac);
    }

    float getHeight(float x, float y);

    void render(Shader *shader, RenderLayer renderLayer);
    virtual ~Terrain();


    void update() override;
};


#endif //ELFGE_TERRAINMESH_H
