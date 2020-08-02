#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float type;
layout (location = 4) in float ao;

out vec2 vTexCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 FragPosLightSpace;

out float Type;
out float Ao;


uniform mat4 projection;
uniform mat4 M;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;

void main()
{

    gl_Position = projection * view * M * vec4(Position, 1.);
    mat3 normalMatrix = transpose(inverse(mat3(view * M)));
    normal = normalize(normalMatrix * Normal);

    Type = type;
    Ao = ao;
    fragPos = (M * vec4(Position, 1.0)).xyz;
    vTexCoord = texCoord;
    FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
}


//
//void main()
//{
//
//    gl_Position = projection * view * M * vec4(Position, 1.);
//    mat3 normalMatrix = transpose(inverse(mat3(view * M)));
//    normal = normalize(normalMatrix * Normal);
//
//    Type = type;
//    Ao = ao;
//    fragPos = (view * M * vec4(Position, 1.0)).xyz;
//    vTexCoord = texCoord;
//    FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
//}
