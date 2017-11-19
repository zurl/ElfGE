//
// Created by 张程易 on 29/10/2017.
//

#include "DefaultModel.h"


DefaultModel::~DefaultModel() {
    for(auto &x : meshes){
        delete x;
    }
}

void DefaultModel::render(Shader *shader, RenderLayer renderLayer) {
    for(auto & x: meshes){
        x->render(shader, renderLayer);
    }
}

void DefaultModel::processNode(aiNode *node, const aiScene *scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.emplace_back(new DefaultMesh(mesh, scene, directory));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

DefaultModel::DefaultModel(const std::string &path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

DefaultModel::DefaultModel(DefaultMesh *mesh) {
    meshes.emplace_back(mesh);
}
