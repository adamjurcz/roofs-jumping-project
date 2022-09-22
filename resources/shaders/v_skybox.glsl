#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 texCoord;

uniform mat4 P;
uniform mat4 V;

void main()
{
    texCoord = aPos;
    gl_Position = P * V * vec4(aPos, 1.0);
} 