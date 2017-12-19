#version 420 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 tone;
layout (location = 2) in vec3 velocity;
layout (location = 3) in int lifespan;

out vec3 _tone;
out vec3 ori;
out vec4 v;

uniform mat4 view;
uniform vec3 anchor;
uniform mat4 projection;

void main()
{
    if(lifespan <= 0) return;
    gl_Position = projection * view * vec4(position+anchor,1.0);
    gl_Position.z = 1.0;
    _tone = tone;
    ori = position+anchor;
    v = projection * view * vec4(position+anchor-velocity,1.0);
    v = v-gl_Position;
}
