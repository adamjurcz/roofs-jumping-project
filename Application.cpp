#include "Application.h"
Application::Application(GLFWwindow* window, unsigned int width, unsigned int height) : window(window), _WIDTH(width), _HEIGHT(height), _RATIO((float)width / (float)height), 
				world(window, width, height) {
}

Application::~Application() {
}

void Application::onUpdate() {
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world.onUpdate(window);

		glfwPollEvents();
	}
}

/*
Application::Application(GLFWwindow* window, unsigned int width, unsigned int height): window(window), _WIDTH(width), _HEIGHT(height), _RATIO((float)width/(float)height)  {
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

	world = new World(width, height);
}

Application::~Application() {
}

void Application::onUpdate() {
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world->onUpdate(window);

		glfwPollEvents();
	}
}

void Application::endProgram() {
		glfwDestroyWindow(window);
		glfwTerminate();
}


void Application::initLib() {
	if (!glfwInit()) {
		fprintf(stderr, "No way to init lib.\n");
		exit(EXIT_FAILURE);
	}
}

GLFWwindow* Application::createWindow() {
	GLFWwindow* window = glfwCreateWindow(_WIDTH, _HEIGHT, "RoofsJumping", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "No way to init window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	return window;
}


GLFWwindow* Application::getWindow() {
	return window;
}
*/