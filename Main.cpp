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

void initLib() {
	if (!glfwInit()) {
		fprintf(stderr, "No way to init lib.\n");
		exit(EXIT_FAILURE);
	}
}

void endProgram(GLFWwindow* window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main() {
	GLFWwindow* window;
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


	Application application(window, _WIDTH, _HEIGHT);
	application.onUpdate();
	endProgram(window);
	exit(EXIT_SUCCESS);
}
