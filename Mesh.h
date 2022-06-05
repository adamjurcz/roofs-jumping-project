#pragma once
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

class Mesh {
private:
	std::vector<Textures>textures;
	std::vector<Vertex>vertices;
	std::vector<GLuint>indices;

	//VAO vao;
	
public:
	
};