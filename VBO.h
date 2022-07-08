#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include "Vertex.h"
class VBO
{
private:
	GLuint vboID;
public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO(Vertex* vertices, GLsizeiptr size);
	void bind();
	void unbind();
	void deactivate();
};

#endif

