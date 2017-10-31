//
// Created by 张程易 on 29/10/2017.
//

#include "DefaultMesh.h"

DefaultMesh::DefaultMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory) {
    this->directory = directory;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        // texture coordinates
        if(mesh->mTextureCoords[0]){
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else vertex.texCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    /** Materials **/

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");

    bindVertice();
}

void DefaultMesh::render(Shader * shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    // Binding All Textures
    for(unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
        // 获取纹理序号（diffuse_textureN 中的 N）
        std::stringstream ss;
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            ss << diffuseNr++;
        else if(name == "texture_specular")
            ss << specularNr++;
        number = ss.str();

        shader->setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void DefaultMesh::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = Utility::getTextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
}

void DefaultMesh::bindVertice() {
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
    glBindVertexArray(0);
}

DefaultMesh::DefaultMesh() {

}

DefaultMesh::~DefaultMesh() {

}
