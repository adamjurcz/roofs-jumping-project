#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"



class Player {
private:

	glm::vec3 startPosition;

	float _SPEED;
	float _GRAVITY;
	float _JUMP;
	float _MOVABLE_HEIGHT;

	glm::vec3 jump();

public:
	Player(unsigned int _WIDTH, unsigned int _HEIGHT, glm::vec3 startPosition);
	void keyboardUpdate(GLFWwindow* window, float deltaTime);
	void mouseUpdate(GLFWwindow* window, float deltaTime);
	void gravityUpdate(float deltaTime);
	//void jumpUpdate(float deltaTime);

	Camera camera;
	glm::vec3 position;

	bool isColliding = false;
	bool isStable = true;
};


#endif