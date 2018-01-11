#version 330 core

#define NR_DIR_LIGHTS 1
#define NR_POINT_LIGHTS 4
#define NR_SPOT_LIGHTS 1

in float visibility;
const vec3 skyColor = vec3(0.5, 0.5, 0.5);

out vec4 FragColor;

struct Material {
    sampler2D rTex;
    sampler2D gTex;
    sampler2D bTex;
    sampler2D aTex;
    sampler2D rNormal;
    sampler2D gNormal;
    sampler2D bNormal;
    sampler2D aNormal;
    sampler2D mix;
    float shininess;
};

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in float height;
in vec3 FragPos;
in vec2 TexCoords;
in vec4 FragPosLightSpace;
in mat3 TBN;

uniform vec3 shadowLightPos;
uniform vec3 viewPos;
uniform DirLight dirLight[NR_DIR_LIGHTS];
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight[NR_SPOT_LIGHTS];
uniform Material material;
uniform sampler2D shadowMap;

// function prototypes
float ShadowCalculation(vec4 fragPosLightSpace);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcTexture(vec2 texCoords);
vec4 CalcNormal(vec2 texCoords);

float near = 0.1;
float far  = 100.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}



float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir){
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    if(projCoords.z > 1.0) return 0.0;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    return shadow;
}

void main(){
    vec3 normal = CalcNormal(TexCoords).rgb;
    vec3 norm = normalize(normal * 2.0 - 1.0);
    vec3 viewDir = TBN * normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < NR_DIR_LIGHTS; i++){
        result += CalcDirLight(dirLight[i], norm, viewDir);
    }
    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        //result += CalcPointLight(pointLight[i], norm, FragPos, viewDir);
        //result += CalcSpotLight(spotLight[i], norm, FragPos, viewDir);
    }
    //FragColor = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0);
    //FragColor = texture(material.diffuse, TexCoords);
    FragColor = vec4(result, 1.0);
    FragColor = mix(vec4(skyColor, 1.0), FragColor, visibility);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = TBN * normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(CalcTexture(TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(CalcTexture( TexCoords));
    vec3 specular = light.specular * spec * vec3(CalcTexture( TexCoords));
    float shadow = 0;
    shadow = ShadowCalculation(FragPosLightSpace, normal, lightDir);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    return lighting;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = TBN * normalize(light.position - FragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * vec3(CalcTexture(TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(CalcTexture(TexCoords));
    vec3 specular = light.specular * spec * vec3(CalcTexture(TexCoords));
    //ambient *= attenuation;
    //diffuse *= attenuation;
    //specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = TBN * normalize(light.position - FragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(CalcTexture(TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(CalcTexture( TexCoords));
    vec3 specular = light.specular * spec * vec3(CalcTexture(TexCoords));
    ambient *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

vec4 CalcTexture(vec2 TexCoords){
    float mA = clamp(height-5, 0, 1);
    float mB = clamp(6-height, 0, 1);

    vec4 textureR = texture(material.rTex,TexCoords);
    vec4 textureG = texture(material.gTex,TexCoords);
    vec4 textureB = texture(material.bTex,TexCoords);
    vec4 textureA = texture(material.aTex,TexCoords);

    return mA * textureA + mB * textureG;
}
vec4 CalcNormal(vec2 TexCoords){
   float mA = clamp(height-5, 0, 1);
   float mB = clamp(6-height, 0, 1);
    vec4 normalR = texture(material.rNormal,TexCoords);
    vec4 normalG = texture(material.gNormal,TexCoords);
    vec4 normalB = texture(material.bNormal,TexCoords);
    vec4 normalA = texture(material.aNormal,TexCoords);
    return mA * normalA + mB * normalG;
}
