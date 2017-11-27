//
// Created by 张程易 on 26/11/2017.
//

#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory) {
    this->directory = directory;
    this->scene = scene;
    globalInverseTransform = aiMatrix4x4ToGlm(&scene->mRootNode->mTransformation);
    globalInverseTransform = glm::inverse(globalInverseTransform);
    initMesh(mesh, scene);
    LoadBones(mesh);
    bindVerticeEx();
}


void AnimatedMesh::render(Shader *shader, RenderLayer renderLayer) {
    glm::mat4 transform(1.0f);
    timeCounter += Utility::deltaTime / 2.0f;

    double duration = scene->mAnimations[0]->mDuration;
    while(timeCounter > duration) timeCounter -= duration;
    computeNodeTransform(timeCounter, scene->mRootNode, transform);
    std::string bonename("bones[");
    for(int i = 0 ; i < bonesInfo.size(); i++){
        //shader->setMat4(bonename + std::to_string(i) + "]", glm::mat4(1.0f));
        shader->setMat4(bonename + std::to_string(i) + "]", bonesInfo[i].transform);
    }
    DefaultMesh::render(shader, renderLayer);
}

void AnimatedMesh::computeNodeTransform(float AnimationTime, const aiNode *pNode, const glm::mat4 &ParentTransform) {
    std::string NodeName(pNode->mName.data);

    const aiAnimation* pAnimation = scene->mAnimations[0];

    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

    glm::mat4 NodeTransformation = aiMatrix4x4ToGlm(&pNode->mTransformation);

    if (pNodeAnim) {
        glm::mat4 iden(1.0f);

        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        glm::mat4 ScalingM = glm::scale(iden,
        glm::vec3(Scaling.x, Scaling.y, Scaling.z));
        //printf("scale = %f %f %f\n", Scaling.x, Scaling.y, Scaling.z);

        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        glm::mat4 TranslationM = glm::translate(iden,glm::vec3(Translation.x,Translation.y,Translation.z));

//        NodeTransformation = glm::translate(NodeTransformation,
//                                            glm::vec3(Translation.x,Translation.y,Translation.z));
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
        aiMatrix4x4 RotationMai = aiMatrix4x4(RotationQ.GetMatrix());
        glm::mat4 RotationM = aiMatrix4x4ToGlm(&RotationMai);

        //printf("translate = %f %f %f\n", Translation.x, Translation.y, Translation.z);
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

unsigned int AnimatedMesh::FindPosition(float AnimationTime, const aiNodeAnim *pNodeAnim) {
    for (unsigned int i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

unsigned int AnimatedMesh::FindRotation(float AnimationTime, const aiNodeAnim *pNodeAnim) {
    assert(pNodeAnim->mNumRotationKeys > 0);
    for (unsigned int i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

unsigned int AnimatedMesh::FindScaling(float AnimationTime, const aiNodeAnim *pNodeAnim) {
    assert(pNodeAnim->mNumScalingKeys > 0);
    for (unsigned int i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
        if (AnimationTime < (float) pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

void AnimatedMesh::CalcInterpolatedPosition(aiVector3D &Out, float AnimationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumPositionKeys == 1) {
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

void AnimatedMesh::CalcInterpolatedRotation(aiQuaternion &Out, float AnimationTime, const aiNodeAnim *pNodeAnim) {
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) {
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

void AnimatedMesh::CalcInterpolatedScaling(aiVector3D &Out, float AnimationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumScalingKeys == 1) {
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
