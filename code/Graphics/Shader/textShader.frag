#version 330 core

out vec4 Color;

in vec2 texcoord;
in vec4 color;

uniform sampler2D defaultTexture;

void main()
{
	Color = vec4(1, 1, 1, texture(defaultTexture, texcoord).r) * color;
}