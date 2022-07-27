#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application.h"

const unsigned int _WIDTH = 1000;
const unsigned int _HEIGHT = 1000;


int main() {
	Application application(_WIDTH, _HEIGHT);
	application.onUpdate();

}


/*
#include "World.h"
GLFWwindow* window;
unsigned int _WIDTH = 1000;
unsigned int _HEIGHT = 1000;

void onUpdate(World world) {
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world.onUpdate(window);

		glfwPollEvents();
	}
}

void endProgram() {
	glfwDestroyWindow(window);
	glfwTerminate();
}


void initLib() {
	if (!glfwInit()) {
		fprintf(stderr, "No way to init lib.\n");
		exit(EXIT_FAILURE);
	}
}

GLFWwindow* createWindow() {
	GLFWwindow* window = glfwCreateWindow(_WIDTH, _HEIGHT, "RoofsJumping", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "No way to init window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	return window;
}


GLFWwindow* getWindow() {
	return window;
}


int main() {
	initLib();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = createWindow();

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, _WIDTH, _HEIGHT);
	glClearColor(0, 1, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	World world(_WIDTH, _HEIGHT);
	onUpdate(world);
}
*/
/*
#include "ShaderProgram.h"
#include "Textures.h"
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
	terrain = new Terrain(*terrainShader);
}


void endProgram(GLFWwindow* window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}

float t = 0.0f;


void drawScene(GLFWwindow* window) {
	glClearColor(0.5f, 1.0f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	player->keyboardUpdate(window, deltaTime);
	player->mouseUpdate(window, deltaTime);
	player->gravityUpdate(deltaTime);

	t += deltaTime * 10;

	glm::mat4 start = glm::mat4(1.0f);
	glm::mat4 proj = player->camera.getProjMatrix();
	glm::mat4 view = player->camera.getViewMatrix();

	skybox->renderSkybox(proj, view);
	/// 
	blockShader->activate();
	blockShader->setVec3("objectColor", glm::vec3(0.4f, 0.2f, 0.7f));
	blockShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	blockShader->setVec3("lightPos", lightPos);
	blockShader->setVec3("viewPos", player->position);

	blockShader->setMat4("P", proj);
	blockShader->setMat4("V", view);
	blockShader->setMat4("M", start);

	simpleBuilding->draw(*blockShader);
	//
	glm::mat4 catModel = glm::rotate(start, 90.0f * 180.0f / 3.1415f, glm::vec3(0.0f, 0.0f, 1.0f));
	catModel = glm::translate(catModel, glm::vec3(0.0f, 4.0f, 0.0f));
	catModel = glm::scale(catModel, glm::vec3(0.3f, 0.3f, 0.3f));

	tryShader->activate();
	tryShader->setMat4("P", proj);
	tryShader->setMat4("V", view);
	tryShader->setMat4("M", catModel);
	model->draw(*tryShader);
	//
	glm::mat4 lightModel = glm::rotate(start, t, glm::vec3(0.0f, 1.0f, 0.0f));
	lightModel = glm::translate(lightModel, glm::vec3(0.0f, 0.0f, -2.5f));
	lightModel = glm::scale(lightModel, glm::vec3(0.3f, 0.3f, 0.3f));
	lightPos = glm::vec3(lightModel[3]);

	lightShader->activate();
	lightShader->setMat4("P", proj);
	lightShader->setMat4("V", view);
	lightShader->setMat4("M", lightModel);
	light->draw(*lightShader);
	//
	glm::mat4 terrainModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -20.0f, 0.0f));

	terrainShader->activate();
	terrainShader->setMat4("P", proj);
	terrainShader->setMat4("V", view);
	terrainShader->setMat4("M", terrainModel);
	
	terrain->terrainRender(*terrainShader, player->position, player->camera.getFar());
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

*/

