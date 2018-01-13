#version 400 core

layout (location = 0) in vec3 position;

//out vec2 textureCoords;
out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPosition;
uniform vec3 lightPosiion;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight[1];

const float tiling = 6.0;

void main(void) {
    vec4 worldPositon = model * vec4(position.xzy,1.0);
	gl_Position = projection * view * worldPositon;
	clipSpace = gl_Position;
	textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5) * tiling;
	toCameraVector = cameraPosition.xyz - worldPositon.xyz;
//	fromLightVector = worldPositon.xyz - fromLightVector;
    fromLightVector = dirLight[0].direction;
}