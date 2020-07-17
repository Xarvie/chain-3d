#version 330 core
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
