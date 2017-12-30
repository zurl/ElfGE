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

uniform DirLight dirLight;
uniform Material material;


in vec4 FragPos;

uniform float far_plane;
uniform vec3 shadowLightPos;

vec3 CalcDirLight(DirLight light);

void main(){
    float spec = pow(1, material.shininess);
    CalcDirLight(dirLight);
    // get distance between fragment and light source
    float lightDistance = length(FragPos.xyz - shadowLightPos);

    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;

    // Write this as modified depth
    gl_FragDepth = lightDistance;
}

vec3 CalcDirLight(DirLight light){
    return vec3(0);
}