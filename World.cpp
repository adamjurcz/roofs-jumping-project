#include "World.h"
World::World(unsigned int _WIDTH, unsigned int _HEIGHT):	player(_WIDTH, _HEIGHT, glm::vec3(-4.0f, 0.0f, 0.0f)), 
							catModel("resources/cat/12221_Cat_v1_l3.obj"), 
							facadeTexture("resources/facade.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, "diff"),
							skyscraper(&facadeTexture), 
							terrain(mainRenderer.terrainShader) {
	this->_WIDTH = _WIDTH;
	this->_HEIGHT = _HEIGHT;
	lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void World::onUpdate(GLFWwindow* window) {
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	fullTime += deltaTime;

	player.keyboardUpdate(window, deltaTime);
	player.mouseUpdate(window, deltaTime);
	player.gravityUpdate(deltaTime);

	glm::mat4 start = glm::mat4(1.0f);
	glm::mat4 proj = player.camera.getProjMatrix();
	glm::mat4 view = player.camera.getViewMatrix();

	skybox.renderSkybox(proj, view);

	mainRenderer.renderSkyscrapers(proj, view, start, &skyscraper, &player, lightPos);
	//
	glm::mat4 model = glm::rotate(start, 90.0f * 180.0f / 3.1415f, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 4.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));

	mainRenderer.renderObjects(proj, view, model, &catModel);
	//
	glm::mat4 lightModel = glm::rotate(start, fullTime, glm::vec3(0.0f, 1.0f, 0.0f));
	lightModel = glm::translate(lightModel, glm::vec3(0.0f, 0.0f, -2.5f));
	lightModel = glm::scale(lightModel, glm::vec3(0.3f, 0.3f, 0.3f));

	lightPos = glm::vec3(lightModel[3]);
	mainRenderer.renderLightCube(proj, view, lightModel, &lightShape);
	//
	glm::mat4 terrainModel = glm::translate(start, glm::vec3(0.0f, -30.0f, 0.0f));
	mainRenderer.renderTerrain(proj, view, terrainModel, &terrain, &player);
	//
	glfwSwapBuffers(window);
}


void World::generateBuildingLocations() {

}

