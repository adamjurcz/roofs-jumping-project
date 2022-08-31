#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 Normal;
out vec3 FragPosition;
out vec2 texCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	gl_Position = P*V*M*vec4(aPos, 1.0);
	FragPosition = vec3(M*vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(M)))*aNormal;
	texCoord = aTex;
}
