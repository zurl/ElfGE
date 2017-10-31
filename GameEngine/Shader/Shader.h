//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_SHADER_H
#define ELFGE_SHADER_H

#include "../Common.h"
#include "../Utility.h"

class Shader {
protected:
    GLuint shaderID;
public:
    Shader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath);
    void use(){
        glUseProgram(this->shaderID);
    }
    inline void setBool(const std::string &name, bool value) const{
        glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
    }
    inline void setInt(const std::string &name, int value) const{
        glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
    }
    inline void setFloat(const std::string &name, float value) const{
        glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
    }
    inline void setMat4(const std::string &name, const glm::mat4 & value){
        glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
    inline void setVec2(const std::string &name, float x, float y) const{
        glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
    }
    inline void setVec2(const std::string &name, const glm::vec2 & v) const{
        glUniform2f(glGetUniformLocation(shaderID, name.c_str()), v.x, v.y);
    }
    inline void setVec3(const std::string &name, float x, float y,float z) const{
        glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
    }
    inline void setVec3(const std::string &name, const glm::vec3 & v) const{
        glUniform3f(glGetUniformLocation(shaderID, name.c_str()), v.x, v.y, v.z);
    }
    inline void setVec4(const std::string &name, float x, float y,float z, float w) const{
        glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
    }
    inline void setVec4(const std::string &name, const glm::vec4 & v) const{
        glUniform4f(glGetUniformLocation(shaderID, name.c_str()), v.x, v.y, v.z, v.w);
    }
};



#endif //ELFGE_SHADER_H
