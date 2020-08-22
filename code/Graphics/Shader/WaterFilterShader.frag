#version 330 core

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














