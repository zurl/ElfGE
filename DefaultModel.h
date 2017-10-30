//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_DEFAULTMODEL_H
#define ELFGE_DEFAULTMODEL_H

#include "Common.h"
#include "Model.h"
#include "DefaultMesh.h"

class DefaultModel: public Model {

    std::vector<Mesh *> meshes;
    std::string directory;
public:

    DefaultModel(Mesh * mesh){
        meshes.emplace_back(mesh);
    }

    DefaultModel(const std::string & path){
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);
    }

    void __render(Shader *shader) override {
        for(auto & x: meshes){
            x->__render(shader);
        }
    }

private:
    void processNode(aiNode *node, const aiScene *scene){
        for(unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.emplace_back(new DefaultMesh(mesh, scene, directory));
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

};


#endif //ELFGE_DEFAULTMODEL_H
