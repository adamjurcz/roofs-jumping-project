#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <bullet/btBulletDynamicsCommon.h>

#include "Camera.h"
#include "PhysicCube.h"
#include "ObjectsManager.h"
#include "Maths.h"


class Player {
private:
	glm::vec3 startPosition;

	
	float _SPEED;
	float _GRAVITY;
	float _JUMP;
	float _MOVABLE_HEIGHT;

	glm::vec3 getPickRay(GLFWwindow* window);
	glm::vec2 getNormalizedCoords(double x, double y, int _WIDTH, int _HEIGHT);

	glm::vec3 jump();

public:
	Player(GLFWwindow* window, unsigned int _WIDTH, unsigned int _HEIGHT, glm::vec3 startPosition);
	void keyboardUpdate(GLFWwindow* window, ObjectsManager& objectsManager, float deltaTime);
	void mouseUpdate(GLFWwindow* window, ObjectsManager& objectsManager, float deltaTime);

	void gravityUpdate(float deltaTime);

	void shootBox(ObjectsManager& objectsManager);
	
	Camera camera;
	glm::vec3 position;
	
	bool isColliding = false;
	bool isStable = true;
};


#endif