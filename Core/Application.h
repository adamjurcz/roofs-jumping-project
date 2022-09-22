#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "World/World.h"


class Application 
{
private:
	const unsigned int _WIDTH;
	const unsigned int _HEIGHT;
	const float _RATIO;

	GLFWwindow* window;
	
	World world;
public:
	Application(GLFWwindow* window, unsigned int width, unsigned int height);
	~Application();
	void onUpdate();
};


#endif
