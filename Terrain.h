#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <vector>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vertex.h"
#include "Textures.h"
#include "Mesh.h"
#include "Maths.h"

class Terrain {
private:
	Mesh* mesh;
	VAO* vao;

	int width, height;

	int NUM_STRIPS;
	int TRAINGL_IN_STRIP;

	float startWidth;
	float startHeight;

public:
	Terrain(ShaderProgram& shader);
	void terrainGenerator(ShaderProgram& shader);
	void terrainRender(ShaderProgram& shader, glm::vec3& playerPos, float zFar);
	
	int positionToStrip(float x);

};


#endif

