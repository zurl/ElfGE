//
// Created by 张程易 on 26/11/2017.
//

#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory,
                           const std::map<std::string, unsigned int> &bonesMap) {
    this->directory = directory;
    initMesh(mesh, scene);
    LoadBones(mesh, bonesMap);
    bindVerticeEx();
}


void AnimatedMesh::LoadBones(const aiMesh *pMesh, const std::map<std::string, unsigned int> &bonesMap) {
    bones.resize(vertices.size());
    for (unsigned int i = 0; i < pMesh->mNumBones; i++) {
        std::string BoneName(pMesh->mBones[i]->mName.data);
        unsigned int BoneIndex = bonesMap.find(BoneName)->second;
        for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
            unsigned int VertexID = pMesh->mBones[i]->mWeights[j].mVertexId;
            float weight = pMesh->mBones[i]->mWeights[j].mWeight;
            for (int k = 0; k < NUM_BONES_PER_VEREX + 1; k++) {
                assert(k != NUM_BONES_PER_VEREX);
                if (bones[VertexID].weights[k] == 0.0) {
                    bones[VertexID].weights[k] = weight;
                    bones[VertexID].IDs[k] = BoneIndex;
                    break;
                }
            }
        }
    }
}

void AnimatedMesh::bindVerticeEx() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, bitangent));

    glGenBuffers(1, &boneVBO);
    glBindBuffer(GL_ARRAY_BUFFER, boneVBO);
    glBufferData(GL_ARRAY_BUFFER, bones.size() * sizeof(VertexBoneData), &bones[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid *) 0);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (void *) offsetof(VertexBoneData, weights));

    glBindVertexArray(0);
}
