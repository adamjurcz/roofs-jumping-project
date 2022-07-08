#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Camera.h"
#include "CommonConsts.h"

class Player {
private:
	const glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 0.0f);

public:
	Player();
	void keyboardUpdate(GLFWwindow* window, float deltaTime);
	void mouseUpdate(GLFWwindow* window, float deltaTime);

	Camera camera;
	glm::vec3 position;

	bool isColliding = false;
	bool isStable = false;
	bool isFalling = false;
	bool isJumping = false;

};


#endif