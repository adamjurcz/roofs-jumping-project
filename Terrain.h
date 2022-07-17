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

	const char* terrainTexture1 = "terrain1.png";
	const char* terrainTexture2 = "terrain2.png";
	const char* terrainTexture3 = "terrain3.png";
public:
	Terrain(ShaderProgram* shader);
	void terrainGenerator(ShaderProgram* shader);
	void terrainRender(ShaderProgram* shader, glm::vec3& playerPos, float zFar);
	
	int positionToStrip(float x);

};


#endif

