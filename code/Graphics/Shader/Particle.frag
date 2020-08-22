#version 330 core

uniform sampler2D defaultTexture;

in vec2 texcoords;
in vec4 color;

void main()
{
	gl_FragColor = texture(defaultTexture, texcoords) * color;
}




