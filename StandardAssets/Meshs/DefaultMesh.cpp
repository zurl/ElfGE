//
// Created by 张程易 on 29/10/2017.
//

#include "DefaultMesh.h"
#include "Graphics/TextureManager.h"

DefaultMesh::DefaultMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory) {
    this->directory = directory;
    initMesh(mesh, scene);
    bindVertice();
}

void DefaultMesh::render(Shader *shader, RenderLayer renderLayer) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    // Binding All Textures
    if (renderLayer == RenderLayer::WORLD) {
        for (unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
            // 获取纹理序号（diffuse_textureN 中的 N）
            std::stringstream ss;
            std::string number;
            std::string name = textures[i].type;
            if (name == "diffuse")
                ss << diffuseNr++;
            else if (name == "specular")
                ss << specularNr++;
            else if (name == "normal")
                ss << normalNr++;
            number = ss.str();

            shader->setInt(("material." + name).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void DefaultMesh::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = TextureManager::loadTexture2D(directory + "/" + str.C_Str());
        texture.type = typeName;
        textures.push_back(texture);
        if (Config::Hack::hack && typeName == "diffuse") {
            char fuckbuffer[128];
            strcpy(fuckbuffer, str.C_Str());
            int len = strlen(fuckbuffer);
            strcpy(fuckbuffer + len - 11, "normal");
            strncpy(fuckbuffer + len - 5, fuckbuffer + len - 4, 5);
            texture.id = TextureManager::loadTexture2D(directory + "/" + fuckbuffer);
            texture.type = "normal";
            textures.push_back(texture);
        }
    }
}

void DefaultMesh::initMesh(aiMesh *mesh, const aiScene *scene) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->mNormals) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        } else {
            vertex.normal = glm::vec3(0.0f);
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        } else vertex.texCoords = glm::vec2(0.0f, 0.0f);
        if (mesh->mTangents) {
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;
        }

        if (mesh->mBitangents) {
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    /** Materials **/

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
    loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
    loadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
    loadMaterialTextures(material, aiTextureType_AMBIENT, "height");
    //loadMaterialTextures(material, _aiTextureType_Force32Bit, "height");
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, bitangent));
    glBindVertexArray(0);
}

DefaultMesh::DefaultMesh() {

}

DefaultMesh::~DefaultMesh() {

}


DefaultMesh::Vertex::Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoords) : position(
        position), normal(normal), texCoords(texCoords) {}

DefaultMesh::Vertex::Vertex() {}

DefaultMesh::Texture::Texture(unsigned int id, const std::string &type) : id(id), type(type) {}

DefaultMesh::Texture::Texture() {}
