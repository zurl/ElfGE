//
// Created by 张程易 on 26/11/2017.
//

#include "AnimatedModel.h"


void AnimatedModel::computeNodeTransform(double AnimationTime, const aiNode *pNode, const glm::mat4 &ParentTransform) {
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

//        glm::quat RotationQ;
//        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
//        glm::mat4 RotationM = glm::toMat4(RotationQ);
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

unsigned int AnimatedModel::FindPosition(double AnimationTime, const aiNodeAnim *pNodeAnim) {
    for (unsigned int i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
        if (AnimationTime < pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

unsigned int AnimatedModel::FindRotation(double AnimationTime, const aiNodeAnim *pNodeAnim) {
    assert(pNodeAnim->mNumRotationKeys > 0);
    for (unsigned int i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        if (AnimationTime < pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

unsigned int AnimatedModel::FindScaling(double AnimationTime, const aiNodeAnim *pNodeAnim) {
    assert(pNodeAnim->mNumScalingKeys > 0);
    for (unsigned int i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
        if (AnimationTime < pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }
    assert(0);
    return 0;
}

void AnimatedModel::CalcInterpolatedPosition(aiVector3D &Out, double AnimationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumPositionKeys == 1 || AnimationTime < pNodeAnim->mPositionKeys[0].mTime) {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }

    unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    if(PositionIndex <= 500){

       // printf("%d\n", PositionIndex);
    }
    unsigned int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    double DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    double Factor = (AnimationTime - pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + (float)Factor * Delta;
}

void AnimatedModel::CalcInterpolatedRotation(aiQuaternion &Out, double AnimationTime, const aiNodeAnim *pNodeAnim) {
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1 || AnimationTime < pNodeAnim->mRotationKeys[0].mTime) {
        const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[0].mValue;
        glm::quat startQ(StartRotationQ.w, StartRotationQ.x, StartRotationQ.y, StartRotationQ.z);
        return;
    }

    unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = (float)pNodeAnim->mRotationKeys[NextRotationIndex].mTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime;
    float Factor = ((float)AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0 && Factor <= 1.0);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
//    printf("%f %f %f %f -> %f %f %f %f\n",
//           StartRotationQ.x, StartRotationQ.y,StartRotationQ.z,StartRotationQ.w,
//           EndRotationQ.x, EndRotationQ.y,EndRotationQ.z,EndRotationQ.w);
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
    //Out = StartRotationQ;
//    glm::quat startQ(StartRotationQ.w, StartRotationQ.x, StartRotationQ.y, StartRotationQ.z);
//    glm::quat endQ(EndRotationQ.w, EndRotationQ.x, EndRotationQ.y, EndRotationQ.z);
//    //Out = startQ;
//    Out = glm::lerp(startQ, endQ, Factor);
}

void AnimatedModel::CalcInterpolatedScaling(aiVector3D &Out, double AnimationTime, const aiNodeAnim *pNodeAnim) {
    if (pNodeAnim->mNumScalingKeys == 1 || AnimationTime < pNodeAnim->mScalingKeys[0].mTime) {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }
    unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    //printf("%d\n", ScalingIndex);
    unsigned int NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
    double DeltaTime = pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime;
    double Factor = (AnimationTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + (float)Factor * Delta;
}

void AnimatedModel::update() {
    glm::mat4 transform(1.0f);
    animation_now += Utility::deltaTime / 10.0f;
    if(animation_now > currentAnimation.end) animation_now = currentAnimation.start;
    computeNodeTransform(animation_now, scene->mRootNode, transform);
}

void AnimatedModel::render(Shader *shader, RenderLayer renderLayer) {
    if(renderLayer == RenderLayer::WORLD_SHADOW){
        shader->setInt("enableBones", 1);
    }
    std::string bonename("bones[");
    for (int i = 0; i < bonesInfo.size(); i++) {
        shader->setMat4(bonename + std::to_string(i) + "]", bonesInfo[i].transform);
    }
    for(auto & x: meshes){
        x->render(shader, renderLayer);
    }
    if(renderLayer == RenderLayer::WORLD_SHADOW){
        shader->setInt("enableBones", 0);
    }
}

AnimatedModel::AnimatedModel(const std::string &path) {

    std::cout<<path<<std::endl;
    scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

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
    auto iter = customAnimationMap.find(name);
    if( iter == customAnimationMap.end()){
        throw Exception("NO ANIMATION FOUND");
    }
    else{
        currentAnimation = iter->second;
        animation_now = currentAnimation.start;
    }
}

void AnimatedModel::registerAnimation(const std::string &name, unsigned int startFrame, unsigned int endFrame) {
    assert(startFrame != 0 && endFrame >= startFrame);
    aiNodeAnim * pNode = pAnimation->mChannels[0];
    Animation animation;
    animation.start = pNode->mScalingKeys[startFrame - 1].mTime;
    animation.end = pNode->mScalingKeys[endFrame].mTime;
    animation.startFrame = startFrame;
    animation.endFrame = endFrame;
    customAnimationMap.emplace(name, animation);
}
