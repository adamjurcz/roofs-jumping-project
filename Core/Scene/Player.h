#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <bullet/btBulletDynamicsCommon.h>


#include "../Camera.h"
#include "../Physics/PhysicCube.h"
#include "../Physics/Physics.h"
#include "ObjectsManager.h"
#include "../Utils/Maths.h"


class Player {
private:
	Physics physics;

	float _SPEED;
	float _GRAVITY;
	float _JUMP;
	float _MOVABLE_HEIGHT;

	glm::vec3 jump();
public:
	Player(GLFWwindow* window, unsigned int _WIDTH, unsigned int _HEIGHT, glm::vec3 startPosition);
	void keyboardUpdate(GLFWwindow* window, ObjectsManager& objectsManager, float deltaTime);
	void mouseUpdate(GLFWwindow* window, ObjectsManager& objectsManager, float deltaTime);

	void gravityUpdate(float deltaTime);
	
	void shootBox(ObjectsManager& objectsManager);
	void checkStability(ObjectsManager& objectsManager);

	
	Camera camera;

	glm::vec3 startPosition;
	glm::vec3 position;
	
	int jumpState = 0; //5- mocny skok, 4- mniejszy itd 0- brak skoku
	bool isStable = false;
};


#endif