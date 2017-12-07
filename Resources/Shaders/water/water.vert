#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
      uniform sampler2D water;

      out vec3 position;
      void main() {
        vec4 info = texture(water, aPos.xy * 0.5 + 0.5);
        position = aPos.xzy;
        position.y += info.r;
        gl_Position =  projection* view*model * vec4(position, 1.0);
      }
