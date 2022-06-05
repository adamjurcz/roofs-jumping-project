#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <stb/stb_image.h>

#include "Camera.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"

class Skybox
{
private:
	GLuint skyboxID;
	const static std::vector<std::string> cubeFaces;
	const static GLfloat skyboxVertices[];

	ShaderProgram* skyboxShader;
	VAO* VAOskybox;
	VBO* VBOskybox;

	void createCubeMap(const std::vector<std::string>& cubeFaces);
public:
	Skybox();
	void renderSkybox(const glm::mat4& proj, const glm::mat4& view);


};

#endif

