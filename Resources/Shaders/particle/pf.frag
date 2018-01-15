#version 330 core
in vec2 TexCoord;
in vec4 tone;
out vec4 color;

uniform sampler2D tex;

void main()
{
    color = vec4(texture(tex, TexCoord)*tone);
    //color.a *= brightness;
}
