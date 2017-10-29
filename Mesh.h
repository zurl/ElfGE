//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_MESH_H
#define ELFGE_MESH_H

#include "Common.h"
#include "Shader.h"

class Mesh {
protected:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        setupMesh();
    }

    void render(Shader * shader){
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

        // Draw Vertices
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    /**
      * The process of setup mesh
      * 1. Create VAO VBO EBO
      * 2. Bind VAO -> VBO
      * 3. Data -> VAO
      * 4. EBO -> VAO
      * 5. Interpret VAO
      */
    void setupMesh(){
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
};


#endif //ELFGE_MESH_H
