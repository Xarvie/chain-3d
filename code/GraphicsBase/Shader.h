//
// Created by caspasex on 2019/10/17.
//

#pragma once
#ifndef SHADER_
#define SHADER_

#include "Config.h"
#include "OpenglHeader.h"
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

static char s2d_frag_glsl [] = R"(#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = texture(texture1, TexCoord.xy);

    //    vec4 color = texture2D(baseTexture, gl_TexCoord[0].xy);
    //    gl_FragColor = color;
}
)";
static char s2d_vert_glsl [] = R"(#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform int offset;
uniform int wcount;
uniform int hcount;
//uniform int allcount;
uniform mat4 M;
uniform mat4 MVP;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    float offsetf = float(offset);
    float wcountf = float(wcount);
    float hcountf = float(hcount);
    gl_Position = MVP * vec4(aPos, 1.0);
    ourColor = aColor;

    float indexf = offsetf;



    TexCoord = vec2(mod(indexf, wcountf) * 1.0 / wcountf + aTexCoord.x / wcountf - 0.001,
    (hcountf - 1.0 - indexf/wcountf) * 1.0 / hcountf + aTexCoord.y / hcountf - 0.001);

}
)";
static char s2dv_frag_glsl [] = R"(#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = texture2D(texture1, TexCoord.xy);

    //    vec4 color = texture2D(baseTexture, gl_TexCoord[0].xy);
    //    gl_FragColor = color;
}
)";
static char s2dv_vert_glsl [] = R"(#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform int offset;
uniform int wcount;
uniform int hcount;
//uniform int allcount;


out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    float offsetf = float(offset);
    float wcountf = float(wcount);
    float hcountf = float(hcount);
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;

    float indexf = offsetf;


    TexCoord = vec2(mod(indexf, wcountf) * 1.0 / wcountf + aTexCoord.x / wcountf,
    (hcountf - 1.0 - indexf/wcountf) * 1.0 / hcountf + aTexCoord.y / hcountf);
}
)";
static char DebugShadowMapping_frag_glsl [] = R"(#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D depthMap;
uniform float near_plane;
uniform float far_plane;

// required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));
}

void main()
{
    float depthValue = texture(depthMap, TexCoords).r;
    // FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
    //FragColor = vec4(vec3(depthValue), 1.0); // orthographic
    FragColor = texture(depthMap, TexCoords);
}
)";
static char DebugShadowMapping_vert_glsl [] = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}
)";
static char Light_frag_glsl [] = R"(#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;



void main(){
    FragColor = vec4(0.2, 0.4, 0.5, 1.0);
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
    BrightColor = vec4(FragColor.rgb, 1.0);
    else
    BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}
)";
static char MosicShader_frag [] = R"(#version 330 core

out vec4 Color;

in vec2 texcoord;
in vec4 color;

uniform float block_size;
uniform vec2 texSize;

uniform sampler2D defaultTexture;

void main()
{
	vec2 tex_pos = texcoord * texSize;

	vec2 mosic = vec2(
		floor(tex_pos.x / block_size) * block_size,
		floor(tex_pos.y / block_size) * block_size
		);

	vec2 tex_coord = vec2(mosic.x / texSize.x, mosic.y / texSize.y);

	Color = texture(defaultTexture, tex_coord) * color;
}
)";
static char MosicShader_vs [] = R"(#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texcoord;
layout(location = 2) in vec4 Color;

out vec2 texcoord;
out vec4 color;

void main()
{
	gl_Position = vec4(Position, 1.0f);
	color = Color;
	texcoord = Texcoord;
}
)";
static char Noise_frag [] = R"(#version 330 core

in vec2 texcoord;
in vec4 color;

uniform sampler2D Texture0;

uniform float persistence;
uniform float octaves;
uniform float offset;
uniform float stride;

vec2 hash22( vec2 p )
{
    p = vec2(dot(p,vec2(127.1,311.7)), dot(p,vec2(269.5,183.3)));

    return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);
}

float hash21(vec2 p)
{
    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 hash33( vec3 p )
{
	p = vec3(dot(p,vec3(12.98,78.23, 98.25)), dot(p,vec3(127.1,311.7, 412.8)), dot(p,vec3(269.5,183.3, 201.5)));

	return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);
}

float noise( in vec2 p )
{
    vec2 i = floor( p );
    vec2 f = fract( p );

    vec2 u = f*f*f*(6.0*f*f - 15.0*f + 10.0);

    return mix( mix( dot( hash22( i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                     dot( hash22( i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( hash22( i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                     dot( hash22( i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

// 3D ��������
float perlin_noise_3d(vec3 p)
{
	vec3 i = floor(p);
	vec3 f = fract(p);

	vec3 u = f * f * f * (6.0 * f * f - 15.0 * f + 10);

	float z0 = mix( mix( dot(hash33(i + vec3(0, 0, 0)), f - vec3(0, 0, 0)),
						 dot(hash33(i + vec3(1, 0, 0)), f - vec3(1, 0, 0)), u.x),
					mix( dot(hash33(i + vec3(0, 1, 0)), f - vec3(0, 1, 0)),
						 dot(hash33(i + vec3(1, 1, 0)), f - vec3(1, 1, 0)), u.x), u.y);

	float z1 = mix( mix( dot(hash33(i + vec3(0, 0, 1)), f - vec3(0, 0, 1)),
						 dot(hash33(i + vec3(1, 0, 1)), f - vec3(1, 0, 1)), u.x),
					mix( dot(hash33(i + vec3(0, 1, 1)), f - vec3(0, 1, 1)),
						 dot(hash33(i + vec3(1, 1, 1)), f - vec3(1, 1, 1)), u.x), u.y);

	return mix(z0, z1, u.z);
}

float noise_fractal(in vec2 p)
{
    p *= 5.0;
    mat2 m = mat2( 1.6,  1.2, -1.2,  1.6 );
    float f  = 0.5000*noise(p); p = m*p;
    f += 0.2500*noise(p); p = m*p;
    f += 0.1250*noise(p); p = m*p;
    f += 0.0625*noise(p); p = m*p;

    return f;
}

float noise_sum_abs(vec2 p)
{
    float f = 0.0;
    p = p * 7.0;
    f += 1.0000 * abs(noise(p)); p = 2.0 * p;
    f += 0.5000 * abs(noise(p)); p = 2.0 * p;
    f += 0.2500 * abs(noise(p)); p = 2.0 * p;
    f += 0.1250 * abs(noise(p)); p = 2.0 * p;
    f += 0.0625 * abs(noise(p)); p = 2.0 * p;

    return f;
}

float value_noise(vec2 p)
{
    p *= 56.0;
    vec2 pi = floor(p);
    vec2 pf = fract(p);

    vec2 w = pf * pf * (3.0 - 2.0 * pf);

    return mix(mix(hash21(pi + vec2(0.0, 0.0)), hash21(pi + vec2(1.0, 0.0)), w.x),
              mix(hash21(pi + vec2(0.0, 1.0)), hash21(pi + vec2(1.0, 1.0)), w.x),
              w.y);
}

float simplex_noise(vec2 p)
{
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;
    // �任���������(0, 0)��
    vec2 i = floor(p + (p.x + p.y) * K1);
    // i - (i.x+i.y)*K2���㵽�������
    // a:����ǰ�����p���������ľ���
    vec2 a = p - (i - (i.x + i.y) * K2);
    vec2 o = (a.x < a.y) ? vec2(0.0, 1.0) : vec2(1.0, 0.0);
    // ������(1.0, 0.0)��(0.0, 1.0)
    // b = p - (i+o - (i.x + i.y + 1.0)*K2);
    vec2 b = a - o + K2;
    // ������(1.0, 1.0)
    // c = p - (i+vec2(1.0, 1.0) - (i.x+1.0 + i.y+1.0)*K2);
    vec2 c = a - 1.0 + 2.0 * K2;
    // ����ÿ�������Ȩ��������r^2 = 0.5
    vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0.0);
    // ÿ��������ݶ������;��������ĵ�ˣ�Ȼ���ٳ���Ȩ������
    vec3 n = h * h * h * h * vec3(dot(a, hash22(i)), dot(b, hash22(i + o)), dot(c, hash22(i + 1.0)));

    // ֮���Գ���70�����ڼ�����nÿ�������ĺ͵����ֵ�Ժ�ó��ģ��������ܱ�֤��n������������Ժ�Ľ����[-1, 1]֮��
    return dot(vec3(70.0, 70.0, 70.0), n);
}

float AddNoise(vec2 p)
{
	float total = 0;
	for(int i = 0; i < octaves; i++){
		float frequency = pow(2, i);
		float amplitude = pow(persistence, i);
		total += noise(p * frequency) * amplitude;
	}
	return total;
}

float AddNoise(vec3 p)
{
	float total = 0;
	for(int i = 0; i < octaves; i++){
		float frequency = pow(2, i);
		float amplitude = pow(persistence, i);
		total += perlin_noise_3d(p * frequency) * amplitude;
	}
	return total;
}

void main()
{


	float f = AddNoise((texcoord + vec2(offset, -offset)) * stride);

	f = (f + 1) * 0.5;

	float f2 = AddNoise((texcoord) * 50);

	f2 = (f2 + 1) * 0.5;

	vec2 oo = vec2(f, f2);

	vec4 tex_color = texture(Texture0, texcoord + oo * 0.05 - 0.025) * color;
	//vec4 tex_color = texture(Texture0, texcoord) * color;

	vec4 tex_color1 = vec4(0, 0.8, 0.4, 1);
	tex_color1.a = 1 - tex_color.b;

	gl_FragColor = tex_color1;

	//gl_FragColor = vec4(f, f, f, 1);
}
)";
static char Noise_vs [] = R"(#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texcoord;
layout(location = 2) in vec4 Color;

uniform mat4x4 MVPMatrix;

out vec2 texcoord;
out vec4 color;

void main()
{
	gl_Position = MVPMatrix * vec4(Position, 1.0f);
	color = Color;
	texcoord = Texcoord;
}
)";
static char Particle_frag [] = R"(#version 330 core

uniform sampler2D defaultTexture;

in vec2 texcoords;
in vec4 color;

void main()
{
	gl_FragColor = texture(defaultTexture, texcoords) * color;
}

)";
static char Particle_frag_glsl [] = R"(#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 particlecolor;

// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;

void main(){
	// Output color = color of the texture at the specified UV
	color = texture( myTextureSampler, UV ) * particlecolor;

}
)";
static char Particle_gs [] = R"(#version 330 core

layout( points ) in;
layout( triangle_strip, max_vertices = 4 ) out;

uniform mat4x4 MVPMatrix;

out vec2 texcoords;
out vec4 color;

in VS_OUT{
	vec4 color;
	float half_size;
} gs_in[];

void main()
{
	color = gs_in[0].color;

	float size = gs_in[0].half_size;

	gl_Position = MVPMatrix * (gl_in[0].gl_Position + vec4(-size, -size, 0, 0));
	texcoords = vec2(0, 0);
	EmitVertex();

	gl_Position = MVPMatrix * (gl_in[0].gl_Position + vec4( size, -size, 0, 0));
	texcoords = vec2(1, 0);
	EmitVertex();

	gl_Position = MVPMatrix * (gl_in[0].gl_Position + vec4(-size,  size, 0, 0));
	texcoords = vec2(0, 1);
	EmitVertex();

	gl_Position = MVPMatrix * (gl_in[0].gl_Position + vec4( size,  size, 0, 0));
	texcoords = vec2(1, 1);
	EmitVertex();

	EndPrimitive();
}
)";
static char Particle_vert_glsl [] = R"(#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 squareVertices;
layout(location = 1) in vec4 xyzs; // Position of the center of the particule and size of the square
layout(location = 2) in vec4 color; // Position of the center of the particule and size of the square

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 particlecolor;

// Values that stay constant for the whole mesh.
uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;
uniform mat4 VP; // Model-View-Projection matrix, but without the Model (the position is in BillboardPos; the orientation depends on the camera)

void main()
{
	float particleSize = xyzs.w; // because we encoded it this way.
	vec3 particleCenter_wordspace = xyzs.xyz;

	vec3 vertexPosition_worldspace =
		particleCenter_wordspace
		+ CameraRight_worldspace * squareVertices.x * particleSize
		+ CameraUp_worldspace * squareVertices.y * particleSize;

	// Output position of the vertex
	gl_Position = VP * vec4(vertexPosition_worldspace, 1.0);

	// UV of the vertex. No special space for this one.
	UV = squareVertices.xy + vec2(0.5, 0.5);
	particlecolor = color;
}


)";
static char Particle_vs [] = R"(#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;

out VS_OUT{
	vec4 color;
	float half_size;
} vs_out;

void main()
{
	gl_Position = vec4(Position.xy, 0, 1.0f);
	vs_out.color = Color;
	vs_out.half_size = Position.z * 0.5f;
}
)";
static char ShadowMappingDepthSkeletal_frag_glsl [] = R"(#version 330 core

void main()
{
     //gl_FragDepth = gl_FragCoord.z;
}
)";
static char ShadowMappingDepthSkeletal_vert_glsl [] = R"(#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vuv;
layout (location = 2) in vec3 vNormal;
layout (location = 3) in ivec4 vBoneIDs;
layout (location = 4) in vec4 vWeights;

const int MAX_BONES = 100;

uniform mat4 M;
uniform mat4 gBones[MAX_BONES];
uniform int anim;
uniform mat4 lightSpaceMatrix;


void main()
{
	if(anim == 0)
	{

		vec3 FragPos = vec3(M * vec4(vPosition, 1.0));
		gl_Position = lightSpaceMatrix * vec4(FragPos, 1.0);
	}
	else
	{
		mat4 BoneTransform = mat4(1.0);
		BoneTransform = gBones[vBoneIDs[0]] * vWeights[0];
		BoneTransform     += gBones[vBoneIDs[1]] * vWeights[1];
		BoneTransform     += gBones[vBoneIDs[2]] * vWeights[2];
		BoneTransform     += gBones[vBoneIDs[3]] * vWeights[3];

		vec3 FragPos = vec3(M * BoneTransform * vec4(vPosition, 1.0));
		gl_Position = lightSpaceMatrix * vec4(FragPos, 1.0);
	}
}

)";
static char ShadowMappingDepthStatic_frag_glsl [] = R"(#version 330 core

void main()
{
     //gl_FragDepth = gl_FragCoord.z;
}
)";
static char ShadowMappingDepthStatic_vert_glsl [] = R"(#version 330 core
layout (location = 0) in vec3 vPosition;

uniform mat4 M;
uniform mat4 lightSpaceMatrix;

void main()
{
	vec3 FragPos = vec3(M * vec4(vPosition, 1.0));
	gl_Position = lightSpaceMatrix * vec4(FragPos, 1.0);
}

)";
static char SkeletalModelWithShadow_frag_glsl [] = R"(#version 330 core

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
    vec2 texelSize = 1.0 / vec2(textureSize(shadowMap, 0));
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

    return shadow / 4.0;
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
    float cosTheta = clamp(dot(n,l),0.0,1.0);
    float cosAlpha = clamp(dot(n,h),0.0,1.0);
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
)";
static char SkeletalModelWithShadow_vert_glsl [] = R"(#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vuv;
layout (location = 2) in vec3 vNormal;
layout (location = 3) in ivec4 vBoneIDs;
layout (location = 4) in vec4 vWeights;

const int MAX_BONES = 100;

uniform mat4 M;
uniform mat4 MVP;
uniform mat4 gBones[MAX_BONES];
uniform int anim;
uniform mat4 lightSpaceMatrix;

out vec2 uv;
out vec3 normal;
out vec3 fragPos;
out vec4 FragPosLightSpace;

void main(){
    if(anim == 0)
    {
        vec4 position = vec4(vPosition, 1);
        gl_Position = MVP * position;
        uv = vuv;
        normal = vec3(M*vec4(vNormal, 0));
        fragPos = vec3(M*position);
        FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
    }
    else{
        mat4 BoneTransform = gBones[vBoneIDs[0]] * vWeights[0];
        BoneTransform += gBones[vBoneIDs[1]] * vWeights[1];
        BoneTransform += gBones[vBoneIDs[2]] * vWeights[2];
        BoneTransform += gBones[vBoneIDs[3]] * vWeights[3];
        vec4 position = BoneTransform * vec4(vPosition, 1);
        gl_Position = MVP * position;
        uv = vuv;
        normal = vec3(M*BoneTransform*vec4(vNormal, 0));
        fragPos = vec3(M*position);
        FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
    }
}

)";
static char TerrainVoxel_frag_glsl [] = R"(#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;



struct Light {
    vec3 direction;
//vec3 ambient;
//vec3 diffuse;
//vec3 specular;
};

in vec2 vTexCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 FragPosLightSpace;


in float Type;
in float Ao;

uniform int shadowOn;
uniform sampler2D shadowMap;

//uniform sampler2D specularTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Light light;


uniform sampler2D diffuseTexture_a;
uniform sampler2D diffuseTexture_t;
uniform sampler2D diffuseTexture_d;


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
    float bias = max(0.001 * (1.0 - dot(normal, lightDir)), 0.001);

    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(shadowMap, 0));
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

    return shadow / 4.0;
}

void main(){
    vec3 result = vec3(0);

    vec3 lightColor = vec3(0.3,0.1,0.3);
    float lightPower = 8.0f;
    vec3 diffuseMaterial;
    if (Type == 3.0)//d
    diffuseMaterial = texture(diffuseTexture_d, vTexCoord).rgb;
    else if (Type == 2.0)//t
    diffuseMaterial = texture(diffuseTexture_t, vTexCoord).rgb;
    else //a
    diffuseMaterial = texture(diffuseTexture_a, vTexCoord).rgb;


    //vec3 specularMaterial = texture(specularTexture, uv).rgb;

    vec3 n = normalize(normal);
    vec3 l = normalize(lightPos-fragPos);
    vec3 v = normalize(viewPos-fragPos);
    vec3 h = normalize(l+v);
    float cosTheta = clamp(dot(n,l),0.0,1.0);
    float cosAlpha = clamp(dot(n,h),0.0,1.0);
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
)";
static char TerrainVoxel_vert_glsl [] = R"(#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float type;
layout (location = 4) in float ao;

out vec2 vTexCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 FragPosLightSpace;

out float Type;
out float Ao;


uniform mat4 projection;
uniform mat4 M;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;

void main()
{

    gl_Position = projection * view * M * vec4(Position, 1.);
    mat3 normalMatrix = transpose(inverse(mat3(view * M)));
    normal = normalize(normalMatrix * Normal);

    Type = type;
    Ao = ao;
    fragPos = (M * vec4(Position, 1.0)).xyz;
    vTexCoord = texCoord;
    FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
}


//
//void main()
//{
//
//    gl_Position = projection * view * M * vec4(Position, 1.);
//    mat3 normalMatrix = transpose(inverse(mat3(view * M)));
//    normal = normalize(normalMatrix * Normal);
//
//    Type = type;
//    Ao = ao;
//    fragPos = (view * M * vec4(Position, 1.0)).xyz;
//    vTexCoord = texCoord;
//    FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
//}

)";
static char WaterFilterShader_frag [] = R"(#version 330 core

out vec4 Color;

in vec2 texcoord;
in vec4 color;

uniform sampler2D Texture0;

uniform vec2 mousePoint;
uniform vec2 coordPoint;
uniform float radius;
uniform float phase;
uniform float wavLen;
uniform float amplitude;

void main()
{
	vec2 new_pos;
	vec2 offset = gl_FragCoord.xy - mousePoint;
	float len = length(offset);

	if(len > radius){
		new_pos = texcoord;
	}
	else{
		// 计算改点振幅
		float amount = amplitude * sin(len / wavLen * 6.28 + phase);

		// 计算能量损失
		amount = amount * (radius - len) / radius;

		if(len != 0){
			amount = amount * wavLen / len;
		}

		// 得到 water ripple 最终迁移位置
		new_pos = texcoord + (texcoord - coordPoint) * amount;
	}

	Color = texture(Texture0, new_pos) * color;
}
)";
static char WaterFilterShader_vs [] = R"(#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texcoord;
layout(location = 2) in vec4 Color;

uniform mat4x4 MVPMatrix;

out vec2 texcoord;
out vec4 color;

void main()
{
	gl_Position = MVPMatrix * vec4(Position, 1.0f);
	color = Color;
	texcoord = Texcoord;
}
)";
static char bloomFinal_frag_glsl [] = R"(#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform bool bloom;
uniform float exposure;

void main()
{
    const float gamma = 2.2;
    vec3 hdrColor = texture(scene, TexCoords).rgb;
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    if(bloom)
        hdrColor += vec3(bloomColor); // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}
)";
static char bloomFinal_vert_glsl [] = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}
)";
static char blur_frag_glsl [] = R"(#version 330 core

out vec4 FragColor;

in vec2 uv;
uniform sampler2D image;
uniform bool horizontal;
//uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);
uniform float weight[5];// = {0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162};
void main()
{
//    weight[0] = 0.2270270270;
//    weight[1] = 0.1945945946;
//    weight[2] = 0.1216216216;
//    weight[3] = 0.0540540541;
//    weight[4] = 0.0162162162;
    vec2 tex_offset = 1.0 / vec2(textureSize(image, 0));
    vec3 result = texture(image, uv).rgb * weight[0];
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, uv + vec2(tex_offset.x * float(i)*1.5, 0.0)).rgb * weight[i];
            result += texture(image, uv - vec2(tex_offset.x * float(i)*1.5, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, uv + vec2(0.0, tex_offset.y * float(i)*1.5)).rgb * weight[i];
            result += texture(image, uv - vec2(0.0, tex_offset.y * float(i)*1.5)).rgb * weight[i];
        }
    }
    FragColor = vec4(result, 1.0);
}
)";
static char blur_vert_glsl [] = R"(#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vuv;

out vec2 uv;

void main()
{
    uv = vuv;
    gl_Position = vec4(vPosition, 1.0);
}
)";
static char blurShader_frag [] = R"(#version 330 core

out vec4 Color;

in vec2 texcoord;
in vec4 color;

uniform sampler2D defaultTexture;

uniform float width;
uniform float height;

void main()
{
	int n = 11;
	float offsetx = 1 / width;
	float offsety = 1 / height;

	vec3 sum = vec3(0);
	for(int i = 0; i < n * n; i++){
		int row = i % n - int(n / 2);
		int col = i / n - int(n / 2);

		sum += vec3(texture(defaultTexture, texcoord + vec2(col * offsetx, row * offsety)));
	}
	sum /= n * n;

	Color = vec4(sum, 1.0f);


	//Color = texture(defaultTexture, texcoord) * color;
	//float v = 0.2126 * Color.r + 0.7152 * Color.g + 0.0722 * Color.b;
	//Color = vec4(v, v, v, 1.0);
}
)";
static char blurShader_vs [] = R"(#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texcoord;
layout(location = 2) in vec4 Color;

out vec2 texcoord;
out vec4 color;

void main()
{
	gl_Position = vec4(Position, 1.0f);
	color = Color;
	texcoord = Texcoord;
}
)";
static char shader_frag_glsl [] = R"(#version 330 core

out vec4 Color;

in vec2 texcoord;
in vec4 color;

uniform sampler2D defaultTexture;

void main()
{
	Color = texture(defaultTexture, texcoord) * color;

}
)";
static char shader_vert_glsl [] = R"(#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texcoord;
layout(location = 2) in vec4 Color;

out vec2 texcoord;
out vec4 color;

uniform int offset;
uniform int wcount;
uniform int hcount;
void main()
{
	gl_Position = vec4(Position, 1.0f);
	color = Color;

    int index = offset;
    float modx = mod(float(index), float(wcount));
	texcoord = vec2(modx * 1.0 / float(wcount) + Texcoord.x / float(wcount),
	(float(hcount) - 1.0 - float(index/wcount)) * 1.0 / float(hcount) + Texcoord.y / float(hcount));
}
)";
static char textShader_frag [] = R"(#version 330 core

out vec4 Color;

in vec2 texcoord;
in vec4 color;

uniform sampler2D defaultTexture;

void main()
{
	Color = vec4(1, 1, 1, texture(defaultTexture, texcoord).r) * color;
}
)";
static char textShader_vs [] = R"(#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texcoord;
layout(location = 2) in vec4 Color;

out vec2 texcoord;
out vec4 color;

void main()
{
	gl_Position = vec4(Position, 1.0f);
	texcoord = Texcoord;
	color = Color;
}
)";


class Shader {
public:
    unsigned int ID;

    Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        //std::string tessControlCode;
        //std::string tessEvalCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        std::ifstream tcShaderFile;
        std::ifstream teShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        tcShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        teShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e) {
            std::cout << "shader err: FILE READ" << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        GLuint vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, vertexPath);


        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, fragmentPath);




        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);

        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }
    Shader(const std::vector<char>&vertexData, const std::vector<char>& fragmentData) {
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
//        //std::string tessControlCode;
//        //std::string tessEvalCode;
//        std::ifstream vShaderFile;
//        std::ifstream fShaderFile;
//        std::ifstream gShaderFile;
//        std::ifstream tcShaderFile;
//        std::ifstream teShaderFile;
//        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        tcShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        teShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
//            vShaderFile.open(vertexPath);
//            fShaderFile.open(fragmentPath);
//            std::stringstream vShaderStream, fShaderStream;
//            vShaderStream << vShaderFile.rdbuf();
//            fShaderStream << fShaderFile.rdbuf();
//            vShaderFile.close();
//            fShaderFile.close();
            vertexCode.assign(vertexData.begin(), vertexData.end());// = vertexData.data();
            fragmentCode.assign(fragmentData.begin(), fragmentData.end());
        }
        catch (std::ifstream::failure &e) {
            std::cout << "shader err: FILE READ" << std::endl;
        }
#if defined(IOS) or defined(__EMSCRIPTEN__)
        vertexCode = ReplaceAll(vertexCode, "#version 330 core","#version 300 es\r\nprecision mediump float;" );
        fragmentCode = ReplaceAll(fragmentCode, "#version 330 core","#version 300 es\r\nprecision mediump float;" );
#endif
        //std::cout << vertexCode << std::endl;
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();


        GLuint vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, vertexCode);

        //std::cout << fragmentCode << std::endl;
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, fragmentCode);




        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);

        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }


    void use() {
        glUseProgram(ID);
    }

    void del() {
        glDeleteProgram(ID);
    }

    void setBool(const std::string &name, bool value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    void setInt(const std::string &name, int value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform1f(l, value);

    }

    void setVec2(const std::string &name, const glm::vec2 &value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const {
        int l = glGetUniformLocation(ID, name.c_str());//TODO 这里需要优化掉,初始化获取Location
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w) {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4Transpose(const std::string &name, const glm::mat4 &mat) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat[0][0]);
    }

private:

    static void checkCompileErrors(GLuint shader, const std::string &type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION: " << type << "\n" << infoLog << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR: " << type << "\n" << infoLog << std::endl;
            }
        }
    }
};


#endif
