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
            const std::string &normalPath = "");

    glm::vec3 getNormal(float x, float y);

    float getHeight(float x, float y);

    virtual ~Terrain();
};


#endif //ELFGE_TERRAINMESH_H
