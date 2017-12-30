#version 330 core

#define NR_DIR_LIGHTS 1

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight[NR_DIR_LIGHTS];
uniform Material material;

vec3 CalcDirLight(DirLight light);

void main(){
    float spec = pow(1, material.shininess);
    CalcDirLight(dirLight[0]);
}

vec3 CalcDirLight(DirLight light){
    return vec3(0);
}
