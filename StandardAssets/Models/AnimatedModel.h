//
// Created by 张程易 on 26/11/2017.
//

#ifndef ELFGE_ANIMATEDMODEL_H
#define ELFGE_ANIMATEDMODEL_H


#include "DefaultModel.h"
#include "../Meshs/AnimatedMesh.h"

class AnimatedModel: public DefaultModel{
    Assimp::Importer import;
public:
    void processNode(aiNode *node, const aiScene *scene) {
        for(unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.emplace_back(new AnimatedMesh(mesh, scene, directory));
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    AnimatedModel(const std::string &path) {

        std::cout<<path<<std::endl;
        scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);
    }

};


#endif //ELFGE_ANIMATEDMODEL_H
