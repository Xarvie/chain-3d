#version 330 core

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