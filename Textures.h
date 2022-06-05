#pragma once
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "ShaderProgram.h"


class Textures
{
private:
	GLuint texturesID;
	GLuint unit;
	GLenum type;
	

	void readTexture(const char* filename, GLenum format);
public:
	Textures(const char* image, GLenum texType, GLuint unit, GLenum format);

	void texUnit(ShaderProgram& shader, const char* uniform);
	void bind();
	void unbind();
	void destroy();
};

