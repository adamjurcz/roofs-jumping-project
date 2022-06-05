#pragma once
#include <glad/glad.h>
class VBO
{
private:
	GLuint vboID;
public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	void bind();
	void unbind();
	void deactivate();
};

