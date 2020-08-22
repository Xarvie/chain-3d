#version 330 core

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