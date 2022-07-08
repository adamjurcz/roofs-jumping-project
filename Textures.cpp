#include "Textures.h"

void Textures::readTexture(const char* filename, GLenum format) {
	stbi_set_flip_vertically_on_load(false);
	int width, height, fileChannels;
	unsigned char* load = stbi_load(filename, &width, &height, &fileChannels, 0);

	//glEnable(type);

	glActiveTexture(GL_TEXTURE0 + unit);
	glGenTextures(1, &texturesID);
	glBindTexture(type, texturesID);

	GLenum internalFormat = 0;

	if (fileChannels == 4) {
		internalFormat = GL_RGBA;
	}
	else if (fileChannels == 3) {
		internalFormat = GL_RGB;
	}
	else if (fileChannels == 1) {
		internalFormat = GL_ALPHA;
	}

	glTexImage2D(type, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, load);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glGenerateMipmap(type);
	stbi_image_free(load);
	glBindTexture(type, 0);
}

Textures::Textures(const char* image, GLenum texType, GLuint unit, GLenum format, std::string lightType) {
	this->type = texType;
	this->unit = unit;
	this->lightType = lightType;
	readTexture(image, format);

}
void Textures::texUnit(ShaderProgram& shader, const char* uniform, unsigned int unit) {
	GLuint texUni = glGetUniformLocation(shader.getShaderID(), uniform);
	shader.activate();
	glUniform1i(texUni, unit);
}


void Textures::bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, texturesID);
}

void Textures::unbind()
{
	glBindTexture(type, 0);
}

void Textures::destroy()
{
	glDeleteTextures(1, &texturesID);
}

std::string Textures::getLightType() {
	return this->lightType;
}