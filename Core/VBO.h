#ifndef VBO_H
#define VBO_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "Models/Vertex.h"
class VBO
{
private:
	GLuint vboID;
public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO(Vertex* vertices, GLsizeiptr size);
	VBO(std::vector<float> vertices, GLsizeiptr size);

	void bind();
	void unbind();
	void deactivate();
};

#endif

