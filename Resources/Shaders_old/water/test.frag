#version 330 core


in vec3 FragPos;            // 物体位置

uniform sampler2D texture1;
out vec4 FragColor;         // 物体最终颜色

void main(){
    FragColor =  vec4(texture(texture1,FragPos.xy*0.5+0.5).r,0,0,1);
//    FragColor =  vec4(1,0,0,1);
}