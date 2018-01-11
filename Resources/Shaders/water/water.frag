#version 400 core

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;
in vec3 fromLightVector;

out vec4 out_Color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
//uniform vec3 lightColor;

const float waveStrength = 0.020;
const vec3 lightColour = vec3(0.5,0.5,0.5);
uniform float moveFactor;
const float shineDamper = 5.0;
const float reflectivity = 0.8;

void main(void) {

    vec2 ndc = (clipSpace.xy)/(clipSpace.w)/2.0 + 0.5;
    vec2 refractTexCoords = vec2(ndc.x,ndc.y);
    vec2 reflectTexCoords = vec2(ndc.x,-ndc.y);

//    vec2 distortion1 = waveStrength * (texture(dudvMap, vec2(textureCoords.x+moveFactor,textureCoords.y)).rg*2.0 - 1.0);
//    vec2 distortion2 = waveStrength *( texture(dudvMap, vec2(-textureCoords.x+moveFactor,textureCoords.y+moveFactor)).rg*2.0 - 1.0);
//    vec2 totalDistortion = distortion1 +distortion2;
    vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x+moveFactor,textureCoords.y)).rg*0.1;
    distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y+moveFactor);
    vec2 totalDistortion = (texture(dudvMap,distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

    reflectTexCoords += totalDistortion;
    reflectTexCoords.x = clamp(reflectTexCoords.x,0.001,0.999);
    reflectTexCoords.y = clamp(reflectTexCoords.y,-0.999,-0.001);

    refractTexCoords += totalDistortion;
    refractTexCoords = clamp(refractTexCoords,0.001,0.999);

    vec3 viewVector = normalize(toCameraVector);
    float refractiveFactor = dot(viewVector,vec3(0.0,1.0,0.0));
    refractiveFactor = pow(refractiveFactor,0.8);
//    refractiveFactor = 0.9;

    vec4 normalMapColour = texture(normalMap, distortedTexCoords);
    vec3 normal = vec3(normalMapColour.r*2.0 - 1.0, normalMapColour.b, normalMapColour.g*2.0-1.0);


	vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
	float specular = max(dot(reflectedLight, viewVector), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColour * specular * reflectivity;

    vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);
    vec4 refractColour = texture(refractionTexture, refractTexCoords);
//	out_Color = mix(reflectColour, refractColour,refractiveFactor) + vec4(specularHighlights,0);
//	out_Color = mix(reflectColour, vec4(0,0.3,0.3,1),0.2);
	out_Color = reflectColour;
	out_Color = refractColour;

}