#version 420 core
in vec2 TexCoord;
in vec3 tone;
out vec4 color;

uniform sampler2D tex;

void main()
{
    color = vec4(texture(tex, TexCoord)*vec4(tone,1.0));
}
