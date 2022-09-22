#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <vector>
#include <memory>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Models/Vertex.h"
#include "../Models/Mesh.h"
#include "../Scene/Textures.h"
#include "../Utils/Maths.h"

class Terrain {
private:
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<VAO> vao;

	int width, height;

	int NUM_STRIPS;
	int TRAINGL_IN_STRIP;

	float startWidth;
	float startHeight;

public:
	Terrain(ShaderProgram& shader);
	~Terrain();
	void terrainGenerator(ShaderProgram& shader);
	void terrainRender(ShaderProgram& shader, glm::vec3& playerPos, float zFar);
	
	int positionToStrip(float x);

};


#endif

