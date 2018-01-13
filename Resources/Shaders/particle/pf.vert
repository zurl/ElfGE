#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 tone;
layout (location = 2) in vec3 velocity;
layout (location = 3) in int lifespan;
layout (location = 4) in float zoomA;

out vec4 _tone;
out vec3 ori;
out vec4 v;
out float zoom;

uniform mat4 view;
uniform vec3 anchor;
uniform mat4 projection;
uniform float size;

void main()
{
    
    gl_Position = projection * view * vec4(position+anchor,1.0);
    //gl_Position.z = 1.0;
    _tone = tone;
    if(lifespan <= 0) _tone.a = 0;
    ori = position+anchor;
    v = projection * view * vec4(position+anchor-velocity,1.0);
    v = v-gl_Position;
    zoom = zoomA * 0.06;
}