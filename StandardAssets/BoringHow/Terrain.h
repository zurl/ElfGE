//
// Created by 张程易 on 25/11/2017.
//

#ifndef ELFGE_TERRAINMESH_H
#define ELFGE_TERRAINMESH_H


#include <Meshs/DefaultMesh.h>

class Terrain: public DefaultMesh {
    unsigned char * heightMap;
public:
    Terrain(const std::string & heightMapPath,
            const std::string & texturePath,
            const std::string &normalPath = "");

    glm::vec3 getNormal(float x,float y) {
        int PosY = x + 512;
        int PosX = y + 512;
        float frac = x + 512 - PosY;
        int pos = PosY * 1024 + PosX;
        glm::vec3 _yA = vertices[pos].normal * (1 - frac) + vertices[pos + 1024].normal * (frac);
        glm::vec3 _yB = vertices[pos+1].normal * (1 - frac) + vertices[pos + 1025].normal * (frac);
        frac = y + 512 - PosX;
        //hero->position.y = -2.75 + _yA * (1-frac) + _yB * frac;
        return (_yA * (1 - frac) + _yB * frac);
    }
    float getHeight(float x, float y) {
        int PosY = x + 512;
        int PosX = y + 512;
        float frac = x + 512 - PosY;
        int pos = PosY * 1024 + PosX;
        float _yA = heightMap[pos * 3] * (1 - frac) + heightMap[pos * 3 + 1024 * 3] * (frac);
        float _yB = heightMap[pos * 3 + 3] * (1 - frac) + heightMap[pos * 3 + 1025 * 3] * (frac);
        frac = y + 512 - PosX;
        //hero->position.y = -2.75 + _yA * (1-frac) + _yB * frac;
        return -2.75 + (_yA * (1 - frac) + _yB * frac) / 20.0; // 20.0这里是scale大小, -2.75有Translation,这里可以加参数
    }

    virtual ~Terrain();
};


#endif //ELFGE_TERRAINMESH_H
