#version 330 core

out vec4 Color;

in vec2 texcoord;
in vec4 color;

uniform sampler2D defaultTexture;

uniform float width;
uniform float height;

void main()
{
	int n = 11;
	float offsetx = 1 / width;
	float offsety = 1 / height;
	
	vec3 sum = vec3(0);
	for(int i = 0; i < n * n; i++){
		int row = i % n - int(n / 2);
		int col = i / n - int(n / 2);
		
		sum += vec3(texture(defaultTexture, texcoord + vec2(col * offsetx, row * offsety)));
	}
	sum /= n * n;
	
	Color = vec4(sum, 1.0f);
	

	//Color = texture(defaultTexture, texcoord) * color;
	//float v = 0.2126 * Color.r + 0.7152 * Color.g + 0.0722 * Color.b;
	//Color = vec4(v, v, v, 1.0);
}








