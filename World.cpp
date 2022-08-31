#include "World.h"
World::World(GLFWwindow* window, unsigned int _WIDTH, unsigned int _HEIGHT) :
	player(window, _WIDTH, _HEIGHT, glm::vec3(-4.0f, 63.0f, 0.0f)),
	catModel("resources/cat/12221_Cat_v1_l3.obj"),
	terrain(mainRenderer.terrainShader)
{
	this->window = window;
	this->_WIDTH = _WIDTH;
	this->_HEIGHT = _HEIGHT;
	lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	physics.initializePhysics();
	objectsManager.initializeObjectsManager(physics);
	generateBuildingLocations(6.0f, 40.0f, 10.0f, 10);
}

World::~World() {
}

void World::onUpdate(GLFWwindow* window) {
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	fullTime += deltaTime;

	physics.updatePhysicScene(deltaTime);

	player.keyboardUpdate(window, objectsManager, deltaTime);
	player.mouseUpdate(window, objectsManager, deltaTime);
	player.gravityUpdate(deltaTime);

	glm::mat4 start = glm::mat4(1.0f);
	glm::mat4 proj = player.camera.getProjMatrix();
	glm::mat4 view = player.camera.getViewMatrix();

	//
	skybox.renderSkybox(proj, view);

	//
	glm::mat4 model = glm::translate(start, glm::vec3(3.0f, 60.0f, 0.0f));
	model = glm::rotate(model, 90.0f * 180.0f / 3.1415f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));


	mainRenderer.renderObjects(proj, view, model, &catModel);

	//
	//lightPos = glm::vec3(lightModel[3]);
	//mainRenderer.renderLightCube(proj, view, lightModel, &lightShape);

	//
	glm::mat4 terrainModel = glm::translate(start, glm::vec3(0.0f, -30.0f, 0.0f));
	mainRenderer.renderTerrain(proj, view, terrainModel, &terrain, &player);

	//
	btScalar scalar[16];
	for (auto &obj: objectsManager.getBuildings()) {
		obj->GetTransform(scalar);
		glm::mat4 buildingModel = Maths::btScalarToMat4(scalar);
		mainRenderer.renderPhysicObject(proj, view, buildingModel, obj, &player, lightPos);
	}

	for (auto& obj : objectsManager.getShootedCubes()) {
		obj->GetTransform(scalar);
		glm::mat4 physicCubeModel = Maths::btScalarToMat4(scalar);
		mainRenderer.renderPhysicObject(proj, view, physicCubeModel, obj, &player, lightPos);
	}


	glfwSwapBuffers(window);
}


void World::generateBuildingLocations(float size, float height, float span,  unsigned int maxLevel) {
	float xPrev = 0.0f;
	float zPrev = 0.0f;
	float xSpan = size + span;
	float zSpan = size + 10.0f;

	objectsManager.addBuilding(btVector3(12.0f, 40.0f, 12.0f), 0.0f, btVector3(3.0f, 3.0f, 3.0f), btVector3(-4.0f, 20.0f, 0.0f), btQuaternion(0, 0, 0, 1));

	xPrev += xSpan;
	zPrev += zSpan;

	for (unsigned int level = 2; level <= maxLevel; level++) {
		for (unsigned int buildingPairs = 1; buildingPairs <= level; buildingPairs++) {
			objectsManager.addBuilding(btVector3(size, height, size), 0.0f, btVector3(3.0f, 3.0f, 3.0f), btVector3(xPrev, 20.0f, zPrev), btQuaternion(0, 0, 0, 1));
			objectsManager.addBuilding(btVector3(size, height, size), 0.0f, btVector3(3.0f, 3.0f, 3.0f), btVector3(xPrev, 20.0f, -zPrev), btQuaternion(0, 0, 0, 1));
			xPrev += xSpan;
		}
		zPrev += zSpan;
	}
}



