//#version 330 core
//
//layout (location = 0) out vec4 FragColor;
//layout (location = 1) out vec4 BrightColor;
//
//uniform sampler2D baseTexture;
//void main()
//{
//    vec4 color = texture2D(baseTexture, gl_TexCoord[0].xy);
//    gl_FragColor = color;
//}

#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = texture2D(texture1, TexCoord.xy);

    //    vec4 color = texture2D(baseTexture, gl_TexCoord[0].xy);
    //    gl_FragColor = color;
}