#version 330 core

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














