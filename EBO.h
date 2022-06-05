#pragma once
#include <glad/glad.h>
class EBO
{
private:
	GLuint eboID;
public:
	EBO(GLuint* vertices, GLsizeiptr size);
	void bind();
	void unbind();
	void deactivate();
};