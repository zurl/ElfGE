#version 330 core
in vec2 TexCoords;
out vec4 result;

uniform sampler2D text;
uniform vec3 color;
uniform int mode;

void main(){
    if(mode == 0){
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        result = vec4(color, 1.0) * sampled;
    }
    else{
        result = texture(text, TexCoords);
    }
}