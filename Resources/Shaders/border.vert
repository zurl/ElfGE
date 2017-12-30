#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 FragPos;
out vec2 TexCoords;
out vec4 FragPosLightSpace;
out mat3 TBN;
out float visibility;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;
uniform float density;
uniform float gradient;

void main()
{

    mat4 scale = mat4(
    1.1,0,0,0,
    0,1.1,0,0,
    0,0,1.1,0,
    0,0,0,1);

    vec3 T = normalize(vec3(model * vec4(aTangent,   0.0)));
    vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal,    0.0)));
    TBN = transpose(mat3(T, B, N));

    FragPos = vec3(model * scale * vec4(aPos, 1.0));


    vec4 pos2camera = view * vec4(FragPos, 1.0);
    float dis2camera = length(pos2camera);
    visibility = exp(-pow((dis2camera * density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);

    TexCoords = aTexCoords;
    gl_Position = projection * pos2camera;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

}