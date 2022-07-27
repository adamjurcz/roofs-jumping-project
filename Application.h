#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "World.h"

class Application 
{
private:
	const unsigned int _WIDTH;
	const unsigned int _HEIGHT;
	const float _RATIO;


	World* world;
	GLFWwindow* window;

	void initLib();
	GLFWwindow* createWindow();
public:
	Application(unsigned int width, unsigned int height);
	void onUpdate();
	void endProgram();
	
	GLFWwindow* getWindow();
};


#endif
