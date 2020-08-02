//#version 330 core
//layout (location = 0) in vec3 vPosition;
//layout (location = 1) in vec2 vuv;
//layout (location = 2) in vec3 vNormal;
//layout (location = 3) in ivec4 vBoneIDs;
//layout (location = 4) in vec4 vWeights;
//
#version 330 core

//void main()
//{
//    gl_Position = ftransform();
//    int index = offset;
//    gl_TexCoord[0] = gl_MultiTexCoord0;
//    gl_TexCoord[0].x = mod(index, wcount) * 1.0 / wcount + gl_TexCoord[0].x / wcount;
//    gl_TexCoord[0].y = (hcount - 1 - index/wcount) * 1.0 / hcount + gl_TexCoord[0].y / hcount;
//}
//


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform int offset;
uniform int wcount;
uniform int hcount;
//uniform int allcount;


out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;

    int index = offset;
    //gl_TexCoord[0] = gl_MultiTexCoord0;
    //gl_TexCoord[0].x = mod(index, wcount) * 1.0 / wcount + gl_TexCoord[0].x / wcount;
    //gl_TexCoord[0].y = (hcount - 1 - index/wcount) * 1.0 / hcount + gl_TexCoord[0].y / hcount;



    TexCoord = vec2(mod(index, wcount) * 1.0 / wcount + aTexCoord.x / wcount,
    (hcount - 1 - index/wcount) * 1.0 / hcount + aTexCoord.y / hcount);
}