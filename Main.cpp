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

#include "myCube.h"


ShaderProgram* lightShader;
ShaderProgram* blockShader;
VAO* vao;
Skybox* skybox;
GLuint uniID;
GLuint texID;
Textures* texture;
glm::vec3 lightPos = glm::vec3(0.0f, -0.3f, -3.5f);

const int _HEIGHT = 1000;
const int _WIDTH = 1000;
const float _RATIO = (float)_WIDTH / (float)_HEIGHT;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), _WIDTH, _HEIGHT);
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
	skybox = new Skybox();
	
	vao = new VAO[2];
	vao[0].bind();
	VBO vbo0(verticesCube, sizeof(verticesCube));
	vao[0].linkAttr(vbo0, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao[0].linkAttr(vbo0, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao[0].linkAttr(vbo0, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao[0].unbind();
	vbo0.unbind();


	texture = new Textures("resources/facade.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
	texture->texUnit(*blockShader, "texture0");

	vao[1].bind();
	VBO vbo1(verticesCube, sizeof(verticesCube));
	vao[1].linkAttr(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao[1].unbind();
	vbo1.unbind();

	

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

	double currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	camera.input(window, deltaTime);

	t += speed*deltaTime*100;

	WorldTransform worldTransform;
	worldTransform.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	worldTransform.setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotation);
	worldTransform.setTranslation(glm::vec3(0.0f, -0.5f, -2.5f));
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)_WIDTH / (float)_HEIGHT, 0.1f, 100.0f);

	skybox->renderSkybox(proj, view);

	blockShader->activate();
	blockShader->setVec3("objectColor", glm::vec3(0.4f, 0.2f, 0.7f));
	blockShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	blockShader->setVec3("lightPos", lightPos);
	blockShader->setVec3("viewPos", camera.getPosition());

	blockShader->setMat4("P", proj);
	blockShader->setMat4("V", view);
	blockShader->setMat4("M", worldTransform.getWorld());
	
	texture->bind();
	vao[0].bind();
	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);
	texture->unbind();
	vao[0].unbind();
	////////////////////
	glm::mat4 model2 = glm::rotate(worldTransform.getWorld(), t, glm::vec3(0.0f, 1.0f, 0.0f));
	model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, -1.0f));
	model2 = glm::scale(model2, glm::vec3(0.3f, 0.3f, 0.3f));
	lightPos = glm::vec3(model2[3]);
	lightShader->activate();
	lightShader->setMat4("P", proj);
	lightShader->setMat4("V", view);
	lightShader->setMat4("M", model2);

	vao[1].bind();
	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);
	vao[1].unbind();
	
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


/*
	GLfloat vertices1[]{
		0.5f, 1.0f, 0.0f,
		0.0f, -2.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	GLfloat vertices2[]{
		-3.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f
	};

	//VBO, VAO, EBO - vertex buffer object, vertex array object, index(element) buffer object
	vao = new VAO[2];
	vao[0].bind();
	VBO vbo0(vertices1, sizeof(vertices1));
	//EBO ebo(indices, sizeof(indices));
	vao[0].linkAttr(vbo0, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); //vbo, layout w v_simple, ilosc elementow w komponencie, typ, wszystkie zmienne dla wierzcholka, offset dla nowej cechy
	vao[0].unbind();
	vbo0.unbind();
	//vao->linkAttr(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

	vao[1].bind();
	VBO vbo1(vertices2, sizeof(vertices2));
	vao[1].linkAttr(vbo1, 0, 3, GL_FLOAT, 3*sizeof(float), (void*)0);
	vao[1].unbind();
	vbo1.unbind();
	.......
	shaderProgram->activate();
	//glUniform1f(uniID, 1.0f);
	vao[0].bind();
	//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	vao[1].bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
*/

/*
void someCrap1() {
		GLfloat vertices1[]{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};

	GLfloat vertices2[]{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f
	};


	//VBO, VAO, EBO - vertex buffer object, vertex array object, index(element) buffer object
	vao = new VAO[2];
	vao[0].bind();
	VBO vbo0(vertices1, sizeof(vertices1));
	vao[0].linkAttr(vbo0, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0); //vbo, layout w v_simple, ilosc elementow w komponencie, typ, wszystkie zmienne dla wierzcholka, offset dla nowej cechy
	vao[0].linkAttr(vbo0, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao[0].unbind();
	vbo0.unbind();


	vao[1].bind();
	VBO vbo1(vertices2, sizeof(vertices2));
	vao[1].linkAttr(vbo1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao[1].linkAttr(vbo1, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao[1].unbind();
	vbo1.unbind();





	float A = (-100.0f - 1.0f) / -99.0f;
	float B = 2.0f * 100.0f * 1.0f / 99.0f;

	float d = 1 / glm::tan(glm::radians(22.5f));
	glm::mat4 proj = glm::mat4( d/_RATIO, 0.0f, 0.0f, 0.0f,
								0.0f, d, 0.0f, 0.0f,
								0.0f, 0.0f, A, B,
								0.0f, 0.0f, 1.0f, 0.0f);
}
*/

/*void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0, 1, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	lightShader = new ShaderProgram("v_light_cube.glsl", NULL, "f_light_cube.glsl");
	blockShader = new ShaderProgram("v_simple.glsl", NULL, "f_simple.glsl");


	vao = new VAO[2];
	vao[0].bind();
	VBO vbo0(vertices3, sizeof(vertices3));
	EBO ebo0(indices3, sizeof(indices3));
	vao[0].linkAttr(vbo0, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao[0].linkAttr(vbo0, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao[0].unbind();
	vbo0.unbind();
	ebo0.unbind();

	texture = new Textures("chuj.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB);
	texture->texUnit(*blockShader, "tex0", 0);

	vao[1].bind();
	VBO vbo1(verticesCube, sizeof(verticesCube));
	vao[1].linkAttr(vbo1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao[1].unbind();
	vbo1.unbind();


}
*/