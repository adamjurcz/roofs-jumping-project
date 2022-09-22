#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Terrain.h"
#include "Skybox.h"
#include "../Shaders/ShaderProgram.h"
#include "../Scene/Textures.h"
#include "../Scene/Renderer.h"
#include "../Scene/ObjectsManager.h"
#include "../Scene/Player.h"
#include "../Camera.h"
#include "../Models/Model.h"
#include "../Shapes/SimpleBuilding.h"
#include "../Physics/Physics.h"
#include "../Physics/PhysicCube.h"



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

	const float yWorldScene = 35.0f;

	GLFWwindow* window;
	unsigned int _WIDTH;
	unsigned int _HEIGHT;
	

	void generateBuildingLocations(float size, float height, float span, unsigned int maxLevel);
	bool checkUnderScene(glm::vec3 position);

public:
	World(GLFWwindow* window, unsigned int _WIDTH, unsigned int _HEIGHT);
	~World();
	void onUpdate(GLFWwindow* window);

};

#endif