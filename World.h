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
#include "Physics.h"
#include "PhysicCube.h"
#include "ObjectsManager.h"


class World
{
private:
	Renderer mainRenderer;
	
	Player player;

	Skybox skybox;

	/// Models 
	Model stemModel;

	Model catModel;

	/// Obj Manager
	ObjectsManager objectsManager;

	///vector of buildings
	std::vector<PhysicCube*> buildings;

	///vector of shooted cubes
	std::vector<PhysicCube*> shootedCubes;

	/// Physics
	Physics physics;

	/// Terrain
	Terrain terrain;

	/// LightShape
	SimpleBuilding lightShape;

	/// Lights
	glm::vec3 lightPos[2];



	float currentFrame = 0.0f;
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;
	float fullTime = 0.0f;

	GLFWwindow* window;
	unsigned int _WIDTH;
	unsigned int _HEIGHT;
	

	void generateBuildingLocations(float size, float height, float span, unsigned int maxLevel);

public:
	World(GLFWwindow* window, unsigned int _WIDTH, unsigned int _HEIGHT);
	~World();
	void onUpdate(GLFWwindow* window);

};

#endif