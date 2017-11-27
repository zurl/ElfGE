#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

const int MAX_BONES = 100;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 bones[MAX_BONES];
uniform int enableBones;

void main()
{
    if(enableBones == 1){
         mat4  BoneTransform = bones[BoneIDs[0]] * Weights[0];
         BoneTransform += bones[BoneIDs[1]] * Weights[1];
         BoneTransform += bones[BoneIDs[2]] * Weights[2];
         BoneTransform += bones[BoneIDs[3]] * Weights[3];
         FragPos = vec3(model * BoneTransform * vec4(aPos, 1.0));
    }
    else{
        FragPos = vec3(model * vec4(aPos, 1.0));
    }
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}