#version 330 core
layout (location = 0) in vec3 vPosition;

uniform mat4 M;
uniform mat4 lightSpaceMatrix;

void main()
{
	vec3 FragPos = vec3(M * vec4(vPosition, 1.0));
	gl_Position = lightSpaceMatrix * vec4(FragPos, 1.0);
}
