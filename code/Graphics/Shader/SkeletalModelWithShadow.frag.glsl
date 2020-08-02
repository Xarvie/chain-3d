#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


struct Light {
    vec3 direction;
    //vec3 ambient;
    //vec3 diffuse;
    //vec3 specular;
};

in vec2 uv;
in vec3 normal;
in vec3 fragPos;
in vec4 FragPosLightSpace;
uniform int shadowOn;
uniform sampler2D shadowMap;

uniform sampler2D diffuseTexture;
//uniform sampler2D specularTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Light light;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -2; x <= 2; ++x)
    {
        for(int y = -2; y <= 2; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0)
    shadow = 0.0;

    return shadow / 4;
}

void main(){
    vec3 result = vec3(0);

    vec3 lightColor = vec3(0.3,0.1,0.3);
    float lightPower = 8.0f;


    vec3 diffuseMaterial = texture(diffuseTexture, uv).rgb;
    //vec3 specularMaterial = texture(specularTexture, uv).rgb;

    vec3 n = normalize(normal);
    vec3 l = normalize(lightPos-fragPos);
    vec3 v = normalize(viewPos-fragPos);
    vec3 h = normalize(l+v);
    float cosTheta = clamp(dot(n,l),0,1);
    float cosAlpha = clamp(dot(n,h),0,1);
    float d = length(lightPos-fragPos);
    float attenuation = 1.0/(d);
    //color
    vec3 ambientColor = diffuseMaterial*vec3(0.1)*lightColor;
    //vec3 diffuseColor = diffuseMaterial*cosTheta;
    //vec3 diffuseColor = diffuseMaterial*lightColor*cosTheta;
    vec3 diffuseColor = diffuseMaterial;
    //vec3 specularColor = specularMaterial*lightColor*pow(cosAlpha,16)*vec3(0.5);

    float shadow = ShadowCalculation(FragPosLightSpace);
    if(shadowOn == 1)
    result += ambientColor + (1.0 - shadow)*(diffuseColor*attenuation*lightPower);
    else
    result += ambientColor + (diffuseColor*attenuation*lightPower);


    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    FragColor = vec4(result, 1.0);
}