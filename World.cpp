#include "World.h"
World::World(GLFWwindow* window, unsigned int _WIDTH, unsigned int _HEIGHT) :
	player(window, _WIDTH, _HEIGHT, glm::vec3(0.0f, 123.0f, 0.0f)),
	stemModel("resources/tree/MapleTreeStem.obj"),
	catModel("resources/cat/12221_Cat_v1_l3.obj"),
	terrain(mainRenderer.terrainShader)
{
	this->window = window;
	this->_WIDTH = _WIDTH;
	this->_HEIGHT = _HEIGHT;

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

	player.checkStability(objectsManager);
	player.gravityUpdate(deltaTime);
	player.keyboardUpdate(window, objectsManager, deltaTime);
	player.mouseUpdate(window, objectsManager, deltaTime);


	physics.updatePhysicScene(deltaTime);

	glm::mat4 start = glm::mat4(1.0f);
	glm::mat4 proj = player.camera.getProjMatrix();
	glm::mat4 view = player.camera.getViewMatrix();

	//
	skybox.renderSkybox(proj, view);

	//
	glm::mat4 catTransformation = glm::translate(start, glm::vec3(3.0f, 60.0f, 0.0f));
	catTransformation = glm::rotate(catTransformation, 90.0f * 180.0f / 3.1415f, glm::vec3(1.0f, 0.0f, 0.0f));
	catTransformation = glm::scale(catTransformation, glm::vec3(0.05f, 0.05f, 0.05f));


	mainRenderer.renderObjects(proj, view, catTransformation, &catModel);
	//
	glm::mat4 terrainModel = glm::translate(start, glm::vec3(0.0f, -30.0f, 0.0f));
	mainRenderer.renderTerrain(proj, view, terrainModel, &terrain, &player);
	//

	btScalar scalar[16];
	
	for (auto &obj: objectsManager.getBuildings()) {
		obj->GetTransform(scalar);
		glm::mat4 buildingTransformation = Maths::btScalarToMat4(scalar);
		//
		glm::mat4 lightTransformation0 = glm::rotate(buildingTransformation, fullTime, glm::vec3(0.0f, 1.0f, 0.0f));
		lightTransformation0 = glm::translate(lightTransformation0, glm::vec3(-18.0f, 50.0f, 0.0f));

		glm::mat4 lightTransformation1 = glm::rotate(buildingTransformation, fullTime, glm::vec3(0.0f, 1.0f, 0.0f));
		lightTransformation1 = glm::translate(lightTransformation1, glm::vec3(0.0f, 50.0f, -18.0f));

		glm::mat4 treeTransformation = glm::translate(buildingTransformation, glm::vec3(0.0f, 40.0f, 0.0f));
		treeTransformation = glm::scale(treeTransformation, glm::vec3(0.5f, 0.5f, 0.5f));

		lightPos[0] = glm::vec3(lightTransformation0[3]);
		lightPos[1] = glm::vec3(lightTransformation1[3]);

		//
		mainRenderer.renderLightCube(proj, view, lightTransformation0, &lightShape);
		mainRenderer.renderLightCube(proj, view, lightTransformation1, &lightShape);

		//
		mainRenderer.renderPhysicObject(proj, view, buildingTransformation, obj, &player, lightPos);

		mainRenderer.renderTree(proj, view, treeTransformation, &stemModel);
		//
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



