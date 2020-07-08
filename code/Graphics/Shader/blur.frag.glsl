#version 330 core

out vec4 FragColor;

in vec2 uv;
uniform sampler2D image;
uniform bool horizontal;
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
    vec2 tex_offset = 1.0 / textureSize(image, 0);
    vec3 result = texture(image, uv).rgb * weight[0];
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, uv + vec2(tex_offset.x * i*1.5, 0.0)).rgb * weight[i];
            result += texture(image, uv - vec2(tex_offset.x * i*1.5, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, uv + vec2(0.0, tex_offset.y * i*1.5)).rgb * weight[i];
            result += texture(image, uv - vec2(0.0, tex_offset.y * i*1.5)).rgb * weight[i];
        }
    }
    FragColor = vec4(result, 1.0);
}