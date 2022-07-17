#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vertex.h"
#include "ShaderProgram.h"
#include "Textures.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"

class Mesh {
private:
	std::vector<Vertex>vertices;
	std::vector<GLuint>indices;
	std::vector<Textures>textures;
	VAO* vao;
	
public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint>indices, std::vector<Textures>textures);

	void draw(ShaderProgram& shader);
	void update();

	VAO* getVao();
	std::vector<Textures>& getTexture();
};

#endif