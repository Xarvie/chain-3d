#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vuv;
layout (location = 2) in vec3 vNormal;

out vec2 uv;
out vec3 normal;
out vec3 fragPos;

uniform mat4 MVP;
uniform mat4 M;

void main(){

    vec4 position = vec4(vPosition, 1);
    gl_Position = MVP * position;
    uv = vuv;
    normal = vec3(M*vec4(vNormal, 0));
    fragPos = vec3(M*position);
}
