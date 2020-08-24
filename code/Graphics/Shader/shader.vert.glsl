#version 330 core

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

	int index = offset;
	gl_Position = vec4(Position, 1.0f);
//	gl_Position = vec4(vec2(mod(index, wcount) * 1.0 / wcount + Position.x / wcount,
//	(hcount - 1.0 - index/wcount) * 1.0 / hcount + Position.y / hcount),Position.z, 1.0f);
	color = Color;
	//texcoord = Texcoord;

	texcoord = vec2(mod(index, wcount) * 1.0 / wcount + Texcoord.x / wcount,
	(hcount - 1.0 - index/wcount) * 1.0 / hcount + Texcoord.y / hcount);
}