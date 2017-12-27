//
// Created by 张程易 on 26/11/2017.
//

#ifndef ELFGE_ANIMATEDMESH_H
#define ELFGE_ANIMATEDMESH_H

#include "DefaultMesh.h"

#define NUM_BONES_PER_VEREX 4

class AnimatedMesh : public DefaultMesh {


    struct VertexBoneData {
        unsigned int IDs[NUM_BONES_PER_VEREX];
        float weights[NUM_BONES_PER_VEREX];
    };

    std::vector<VertexBoneData> bones;

    void LoadBones(const aiMesh *pMesh, const std::map<std::string, unsigned int> &bonesMap);

    unsigned int boneVBO;

    void bindVerticeEx();

public:

    AnimatedMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory,
                 const std::map<std::string, unsigned int> &bonesMap);


};


#endif //ELFGE_ANIMATEDMESH_H
