#include "VAO.h"
VAO::VAO()
{
	glGenVertexArrays(1, &vaoID);
}


void VAO::linkAttr(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.bind();
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	VBO.unbind();
}


void VAO::bind()
{
	glBindVertexArray(vaoID);
}


void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::deactivate()
{
	glDeleteVertexArrays(1, &vaoID);
}