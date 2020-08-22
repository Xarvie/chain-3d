#version 330 core

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