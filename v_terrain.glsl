#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out float Height;
//out vec3 Position;
out vec2 texCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
    Height = aPos.y;

    texCoord = aTex;
    gl_Position = P * V * M * vec4(aPos, 1.0);
}