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
