#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "ShaderProgram.h"
#include "Textures.h"
#include "WorldTransform.h"
#include "Camera.h"
#include "Skybox.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Model.h"
#include "SimpleBuilding.h"
#include "Player.h"
#include "Terrain.h"

ShaderProgram* lightShader;
ShaderProgram* blockShader;
ShaderProgram* tryShader;
ShaderProgram* terrainShader;

Terrain* terrain;
Skybox* skybox;
Textures* texture;
Model* model;
SimpleBuilding* simpleBuilding;
SimpleBuilding* light;
glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, -3.5f);

Player* player;
float rotation = 0.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void initLib() {
	if (!glfwInit()) { 
		fprintf(stderr, "No way to init lib.\n");
		exit(EXIT_FAILURE);
	}
}


void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0, 1, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	lightShader = new ShaderProgram("v_light_cube.glsl", NULL, "f_light_cube.glsl");
	blockShader = new ShaderProgram("v_simple.glsl", NULL, "f_simple.glsl");
	tryShader = new ShaderProgram("v_try.glsl", NULL, "f_try.glsl");
	terrainShader = new ShaderProgram("v_terrain.glsl", NULL, "f_terrain.glsl");
	skybox = new Skybox();
	
	texture = new Textures("resources/facade.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, "diff");
	simpleBuilding = new SimpleBuilding(texture);
	light = new SimpleBuilding();
	model = new Model("resources/cat/12221_Cat_v1_l3.obj");
	
	player = new Player();
	terrain = new Terrain(terrainShader);

}


void endProgram(GLFWwindow* window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}

float t = 0.0f;
float speed = 0.1f;

void drawScene(GLFWwindow* window) {
	glClearColor(0.5f, 1.0f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	player->keyboardUpdate(window, deltaTime);
	player->mouseUpdate(window, deltaTime);

	t += speed * deltaTime * 10;

	WorldTransform worldTransform;
	worldTransform.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	worldTransform.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotation);
	worldTransform.setTranslation(glm::vec3(0.0f, -0.5f, -2.5f));
	//glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)_WIDTH / (float)_HEIGHT, 0.1f, 100.0f);
	//glm::mat4 view = camera.getViewMatrix();
	glm::mat4 proj = player->camera.getProjMatrix();
	glm::mat4 view = player->camera.getViewMatrix();
	skybox->renderSkybox(proj, view);
	simpleBuilding->simpleBuildingRender(proj, view, worldTransform.getWorld(), lightPos, player->position, blockShader);
	//
	tryShader->activate();
	tryShader->setMat4("P", proj);
	tryShader->setMat4("V", view);

	glm::mat4 catModel = glm::rotate(worldTransform.getWorld(), 90.0f * 180.0f / 3.1415f, glm::vec3(0.0f, 0.0f, 1.0f));
	catModel = glm::translate(catModel, glm::vec3(0.0f, 4.0f, 0.0f));
	catModel = glm::scale(catModel, glm::vec3(0.3f, 0.3f, 0.3f));

	tryShader->setMat4("M", catModel);
	model->draw(*tryShader);
	//
	glm::mat4 model2 = glm::rotate(worldTransform.getWorld(), t, glm::vec3(0.0f, 1.0f, 0.0f));
	model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, -2.5f));
	model2 = glm::scale(model2, glm::vec3(0.3f, 0.3f, 0.3f));
	lightPos = glm::vec3(model2[3]);
	light->simpleBuildingRender(proj, view, model2);
	//
	terrainShader->activate();
	terrainShader->setMat4("P", proj);
	terrainShader->setMat4("V", view);

	glm::mat4 terrainModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -20.0f, 0.0f));
	terrainShader->setMat4("M", terrainModel);
	
	terrain->terrainRender(terrainShader, player->position, player->camera.getFar());
	//
	glfwSwapBuffers(window);
}

GLFWwindow* initWindow() {
	GLFWwindow* window = glfwCreateWindow(_WIDTH, _HEIGHT, "RoofsJumping", NULL, NULL); 
	if (!window)
	{
		fprintf(stderr, "No way to init window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	return window;
}


int main() {
	initLib();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = initWindow();
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, _WIDTH, _HEIGHT);

	initOpenGLProgram(window);

	while (!glfwWindowShouldClose(window)) 
	{
		drawScene(window);
		glfwPollEvents(); 
	}

	endProgram(window);
	return 0;
}


