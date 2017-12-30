<<<<<<< HEAD
#version 420 core
in vec2 TexCoord;
in vec3 tone;
out vec4 color;

uniform sampler2D tex;

void main()
{
    color = vec4(texture(tex, TexCoord)*vec4(tone,1.0));
}
=======
#version 420 core
in vec2 TexCoord;
in vec3 tone;
out vec4 color;

uniform sampler2D tex;

void main()
{
    color = vec4(texture(tex, TexCoord)*vec4(tone,1.0));
}
>>>>>>> cc0a41dba0bd3d38336a37d67b530daa97c0f806
