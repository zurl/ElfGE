//
// Created by 张程易 on 26/11/2017.
//

#ifndef ELFGE_ANIMATEDMESH_H
#define ELFGE_ANIMATEDMESH_H

#include "DefaultMesh.h"

#define NUM_BONES_PER_VEREX 4

class AnimatedMesh: public DefaultMesh {
public:
    struct BoneInfo {
        glm::mat4 offset;
        glm::mat4 transform;
    };

    struct VertexBoneData {
        unsigned int IDs[NUM_BONES_PER_VEREX];
        float weights[NUM_BONES_PER_VEREX];
    };

    std::vector<BoneInfo> bonesInfo;
    std::vector<VertexBoneData> bones;
    std::map<std::string, unsigned int> bonesMap;
    unsigned int bonesCnt = 0;

    const aiScene *scene;

    glm::mat4 globalInverseTransform;

    double timeCounter = 0.0f;

    AnimatedMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory);

    inline glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4 * from){
        //return glm::transpose(glm::make_mat4(&from->a1));
        glm::mat4 to;
        to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1; to[0][3] = (GLfloat)from->d1;
        to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2; to[1][3] = (GLfloat)from->d2;
        to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3; to[2][3] = (GLfloat)from->d3;
        to[3][0] = (GLfloat)from->a4; to[3][1] = (GLfloat)from->b4;  to[3][2] = (GLfloat)from->c4; to[3][3] = (GLfloat)from->d4;
        return to;
    }

    void LoadBones(const aiMesh * pMesh) {
        bones.resize(vertices.size());
        for (uint i = 0 ; i < pMesh->mNumBones ; i++) {
            uint BoneIndex = 0;
            std::string BoneName(pMesh->mBones[i]->mName.data);
            if (bonesMap.find(BoneName) == bonesMap.end()) {
                BoneIndex = bonesCnt;
                bonesCnt++;
                bonesInfo.emplace_back();
            }
            else {
                BoneIndex = bonesMap[BoneName];
            }
            bonesMap[BoneName] = BoneIndex;
            bonesInfo[BoneIndex].offset = aiMatrix4x4ToGlm(&pMesh->mBones[i]->mOffsetMatrix);
            for (uint j = 0 ; j < pMesh->mBones[i]->mNumWeights ; j++) {
                uint VertexID = pMesh->mBones[i]->mWeights[j].mVertexId;
                float weight = pMesh->mBones[i]->mWeights[j].mWeight;
                for(int k = 0; k < NUM_BONES_PER_VEREX + 1; k++){
                    assert( k != NUM_BONES_PER_VEREX);
                    if(bones[VertexID].weights[k] == 0.0){
                        bones[VertexID].weights[k] = weight;
                        bones[VertexID].IDs[k] = BoneIndex;
                        break;
                    }
                }
            }
        }
    }

    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName) {
        for (uint i = 0 ; i < pAnimation->mNumChannels ; i++) {
            const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

            if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
                return pNodeAnim;
            }
        }

        return NULL;
    }

    unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);

    unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);

    unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    void computeNodeTransform(float AnimationTime, const aiNode* pNode, const glm::mat4 & ParentTransform);

    unsigned int boneVBO;

    void bindVerticeEx() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(3);


        glGenBuffers(1, &boneVBO);
        glBindBuffer(GL_ARRAY_BUFFER, boneVBO);
        glBufferData(GL_ARRAY_BUFFER, bones.size() * sizeof(VertexBoneData), &bones[0], GL_STATIC_DRAW);
        glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (void*)offsetof(VertexBoneData, weights));

        glBindVertexArray(0);
    }

    void render(Shader * shader, RenderLayer renderLayer);

};


#endif //ELFGE_ANIMATEDMESH_H
