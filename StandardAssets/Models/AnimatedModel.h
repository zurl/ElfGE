//
// Created by 张程易 on 26/11/2017.
//

#ifndef ELFGE_ANIMATEDMODEL_H
#define ELFGE_ANIMATEDMODEL_H


#include "DefaultModel.h"
#include "../Meshs/AnimatedMesh.h"

class AnimatedModel: public DefaultModel{
    Assimp::Importer import;

    struct BoneInfo {
        glm::mat4 offset;
        glm::mat4 transform;
    };

    std::vector<BoneInfo> bonesInfo;

    std::map<std::string, unsigned int> bonesMap;
    std::map<std::string, unsigned int> animationMap;
    unsigned int bonesCnt = 0;
    const aiAnimation* pAnimation;

    double duration = 0;

    double timeCounter = 0.0f;

    const aiScene *scene;

    glm::mat4 globalInverseTransform;


    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);

    unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);

    unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);

    unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    void computeNodeTransform(float AnimationTime, const aiNode* pNode, const glm::mat4 & ParentTransform);


    void processNode(aiNode *node, const aiScene *scene);


public:
    AnimatedModel(const std::string &path);

    void render(Shader *shader, RenderLayer renderLayer) override;

    void update() override;

    void playAnimation(const std::string & name);

};


#endif //ELFGE_ANIMATEDMODEL_H
