#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
private:
	int windowWidth, windowHeight;
	float lastX, lastY;
	float sensivity = 10.0f;
	float pSpeed = 100.0f;
	float acceleration = 0.1f;

	float yaw = 0.0f;
	float pitch = 0.0f;

	bool firstClick = false;

	void keyboardInput(GLFWwindow* window, double deltaTime);
	void mouseInput(GLFWwindow* window, double deltaTime);
	void updateVectors();

public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, -3.0f);
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	
	Camera(glm::vec3 position, int windowWidth, int windowHeight);

	void input(GLFWwindow* window, double deltaTime);

	glm::mat4 getViewMatrix();
	glm::vec3 getPosition();
};

#endif