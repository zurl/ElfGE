#version 330 core


in vec3 Normal;             // 物体法向量
in vec3 FragPos;            // 物体位置
in vec2 TexCoords;

out vec4 FragColor;         // 物体最终颜色

void main(){
    FragColor =  vec4(1,0,0,1);
}