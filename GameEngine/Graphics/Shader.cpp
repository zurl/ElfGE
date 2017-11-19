//
// Created by 张程易 on 29/10/2017.
//

#include "Shader.h"

Shader::Shader(const std::string &vertexShaderPath,
               const std::string &fragmentShaderPath,
               const std::string & geometryShaderPath) {
    bool enableGeometry = geometryShaderPath != "";
    const char * vertexShaderSource = Utility::getTextFromFile(
            (Utility::RESOURCE_PREFIX + "Shaders/" + vertexShaderPath + ".vert").c_str()
    );
    const char * fragmentShaderSource = Utility::getTextFromFile(
            (Utility::RESOURCE_PREFIX + "Shaders/" + vertexShaderPath + ".frag").c_str()
    );
    if( vertexShaderSource == nullptr || fragmentShaderSource == nullptr){
        throw Exception("Illegal Shader Position");
    }
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::cout << "AT:" << vertexShaderPath << std::endl;
    }
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::cout << "AT:" << vertexShaderPath << std::endl;
    }
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    if(enableGeometry) {
        GLuint geometryShader;
        const char * geometryShaderSource = Utility::getTextFromFile(
                (Utility::RESOURCE_PREFIX + "Shaders/" + geometryShaderPath + ".geom").c_str()
        );
        if( geometryShaderSource == nullptr){
            throw Exception("Illegal Shader Position");
        }
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
        glCompileShader(geometryShader);
        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::GEOM::COMPILATION_FAILED\n" << infoLog << std::endl;
            std::cout << "AT:" << geometryShaderPath << std::endl;
        }
        glAttachShader(shaderID, geometryShader);
    }
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::cout << "AT:" << vertexShaderPath << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
