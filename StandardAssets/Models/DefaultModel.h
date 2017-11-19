//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_DEFAULTMODEL_H
#define ELFGE_DEFAULTMODEL_H

#include "GameEngine.h"
#include "../Meshs/DefaultMesh.h"

class DefaultModel: public Model {

    std::string directory;

public:

    std::vector<DefaultMesh *> meshes;

    DefaultModel(DefaultMesh * mesh);

    DefaultModel(const std::string & path);

    void render(Shader *shader, RenderLayer renderLayer) override;

    virtual ~DefaultModel();

private:
    void processNode(aiNode *node, const aiScene *scene);

};


#endif //ELFGE_DEFAULTMODEL_H
