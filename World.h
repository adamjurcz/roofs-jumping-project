#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "ShaderProgram.h"
#include "Textures.h"
#include "Camera.h"
#include "Skybox.h"
#include "Model.h"
#include "SimpleBuilding.h"
#include "Player.h"
#include "Terrain.h"
#include "Renderer.h"

class World
{
private:
	Renderer mainRenderer;
	
	Player player;

	Skybox skybox;

	/// Textures
	Textures facadeTexture;

	/// Models 
	Model catModel;

	/// Buildings
	SimpleBuilding skyscraper;
	SimpleBuilding lightShape;

	/// Terrain
	Terrain terrain;

	glm::vec3 lightPos;

	float currentFrame = 0.0f;
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;
	float fullTime = 0.0f;

	unsigned int _WIDTH;
	unsigned int _HEIGHT;
	
	void generateBuildingLocations();


public:
	World(unsigned int _WIDTH, unsigned int _HEIGHT);

	void onUpdate(GLFWwindow* window);

};

#endif