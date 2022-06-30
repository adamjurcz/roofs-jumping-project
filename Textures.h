#ifndef TEXTURES_H
#define TEXTURES_H
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "ShaderProgram.h"


class Textures
{
private:
	GLuint texturesID;
	GLuint unit;
	GLenum type;

	std::string lightType;
	
	void readTexture(const char* filename, GLenum format);
public:
	Textures(const char* image, GLenum texType, GLuint unit, GLenum format, std::string lightType);

	void texUnit(ShaderProgram& shader, const char* uniform, unsigned int unit);
	void bind();
	void unbind();
	void destroy();

	std::string getLightType();
};

#endif