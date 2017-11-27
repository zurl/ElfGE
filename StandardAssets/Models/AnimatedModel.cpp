//
// Created by 张程易 on 26/11/2017.
//

#include "AnimatedModel.h"


void AnimatedModel::computeNodeTransform(float AnimationTime, const aiNode *pNode, const glm::mat4 &ParentTransform) {
    std::string NodeName(pNode->mName.data);

    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

    glm::mat4 NodeTransformation = Utility::aiMatrix4x4ToGlm(&pNode->mTransformation);

    if (pNodeAnim) {
        glm::mat4 iden(1.0f);
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        glm::mat4 ScalingM = glm::scale(iden,
                                        glm::vec3(Scaling.x, Scaling.y, Scaling.z));
        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        glm::mat4 TranslationM = glm::translate(iden,glm::vec3(Translation.x,Translation.y,Translation.z));
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
        aiMatrix4x4 RotationMai = aiMatrix4x4(RotationQ.GetMatrix());
        glm::mat4 RotationM = Utility::aiMatrix4x4ToGlm(&RotationMai);
        NodeTransformation = TranslationM * RotationM * ScalingM;
    }

    glm::mat4 GlobalTransformation = ParentTransform * NodeTransformation;

    if (bonesMap.find(NodeName) != bonesMap.end()) {
        uint BoneIndex = bonesMap[NodeName];
        bonesInfo[BoneIndex].transform = globalInverseTransform * GlobalTransformation * bonesInfo[BoneIndex].offset;
        // * bonesInfo[BoneIndex].offset;
    }

    for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
        computeNodeTransform(AnimationTime, pNode->mChildren[i], GlobalTransformation);
    }
}

unsigned int AnimatedModel::FindPosition(float AnimationTime, const aiNodeAnim *pNodeAnim) {
    for (unsigned int i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

unsigned int AnimatedModel::FindRotation(float AnimationTime, const aiNodeAnim *pNodeAnim) {
    assert(pNodeAnim->mNumRotationKeys > 0);
    for (unsigned int i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

unsigned int AnimatedModel::FindScaling(float AnimationTime, const aiNodeAnim *pNodeAnim) {
    assert(pNodeAnim->mNumScalingKeys > 0);
    for (unsigned int i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
        if (AnimationTime < (float) pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

void AnimatedModel::CalcInterpolatedPosition(aiVector3D &Out, float AnimationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumPositionKeys == 1 || AnimationTime < pNodeAnim->mPositionKeys[0].mTime) {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }

    unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    unsigned int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

void AnimatedModel::CalcInterpolatedRotation(aiQuaternion &Out, float AnimationTime, const aiNodeAnim *pNodeAnim) {
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1 || AnimationTime < pNodeAnim->mRotationKeys[0].mTime) {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }

    unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}

void AnimatedModel::CalcInterpolatedScaling(aiVector3D &Out, float AnimationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumScalingKeys == 1 || AnimationTime < pNodeAnim->mScalingKeys[0].mTime) {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }

    unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    unsigned int NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

void AnimatedModel::update() {
    glm::mat4 transform(1.0f);
    timeCounter += Utility::deltaTime;
    while(timeCounter > duration) timeCounter -= duration;
    computeNodeTransform(timeCounter, scene->mRootNode, transform);
}

void AnimatedModel::render(Shader *shader, RenderLayer renderLayer) {
    std::string bonename("bones[");
    for(int i = 0 ; i < bonesInfo.size(); i++){
        shader->setMat4(bonename + std::to_string(i) + "]", bonesInfo[i].transform);
    }
    for(auto & x: meshes){
        x->render(shader, renderLayer);
    }
}

AnimatedModel::AnimatedModel(const std::string &path) {

    std::cout<<path<<std::endl;
    scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);

    globalInverseTransform = Utility::aiMatrix4x4ToGlm(&scene->mRootNode->mTransformation);
    globalInverseTransform = glm::inverse(globalInverseTransform);

    pAnimation = scene->mAnimations[0];
    duration = pAnimation->mDuration;
    for(int i = 0; i < scene->mNumAnimations; i++){
        const aiAnimation * pAnim = scene->mAnimations[i];
        std::string name(pAnim->mName.data);
        std::cout<<name<<": "<<i<<std::endl;
        animationMap.emplace(name, i);
    }

}

void AnimatedModel::processNode(aiNode *node, const aiScene *scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        for (uint j = 0 ; j < mesh->mNumBones ; j++) {
            uint BoneIndex = 0;
            std::string BoneName(mesh->mBones[j]->mName.data);
            if (bonesMap.find(BoneName) == bonesMap.end()) {
                BoneIndex = bonesCnt;
                bonesCnt++;
                bonesInfo.emplace_back();
            } else {
                BoneIndex = bonesMap[BoneName];
            }
            bonesMap[BoneName] = BoneIndex;
            bonesInfo[BoneIndex].offset = Utility::aiMatrix4x4ToGlm(&mesh->mBones[j]->mOffsetMatrix);
        }
        meshes.emplace_back(new AnimatedMesh(mesh, scene, directory, bonesMap));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}


const aiNodeAnim *AnimatedModel::FindNodeAnim(const aiAnimation *pAnimation, const std::string NodeName) {
    for (uint i = 0 ; i < pAnimation->mNumChannels ; i++) {
        const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

        if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
            return pNodeAnim;
        }
    }

    return NULL;
}

void AnimatedModel::playAnimation(const std::string &name) {
    auto iter = animationMap.find(name);
    if( iter == animationMap.end()){
        throw Exception("NO ANIMATION FOUND");
    }
    else{
        pAnimation = scene->mAnimations[iter->second];
        duration = pAnimation->mDuration;
        timeCounter = 0.0f;
    }
}
