#include "Camera.h"
Camera::Camera(glm::vec3 position, int windowWidth, int windowHeight) {
	this->position = position;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	this->lastX = static_cast<float>(this->windowWidth / 2);
	this->lastY = static_cast<float>(this->windowHeight / 2);

	updateVectors();
}

void Camera::input(GLFWwindow* window, double deltaTime) {
	keyboardInput(window, deltaTime);
	mouseInput(window, deltaTime);
}

void Camera::keyboardInput(GLFWwindow* window, double deltaTime) {
	pSpeed = static_cast<float>(deltaTime * 3.4);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += pSpeed * front;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += pSpeed * -glm::normalize(glm::cross(front, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += pSpeed * -front;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += pSpeed * glm::normalize(glm::cross(front, up));
	}
}

void Camera::mouseInput(GLFWwindow* window, double deltaTime) {
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseY = -mouseY;
	if (this->firstClick == false) {
		this->lastX = mouseX;
		this->lastY = mouseY;
		this->firstClick = true;
	}
	float xOffset = (static_cast<float>(mouseX) - this->lastX) * this->sensivity * static_cast<float>(deltaTime);
	float yOffset = (static_cast<float>(mouseY) - this->lastY) * this->sensivity * static_cast<float>(deltaTime);

	this->lastX = mouseX;
	this->lastY = mouseY;

	this->yaw += xOffset;
	this->pitch += yOffset;

	if (this->pitch > 89.0f) {
		this->pitch = 89.0f;
	}
	if (this->pitch < -89.0f) {
		this->pitch = -89.0f;
	}

	updateVectors();
}

void Camera::updateVectors() {
	glm::vec3 newFront = glm::normalize(glm::vec3(
		glm::cos(glm::radians(this->pitch)) * glm::cos(glm::radians(this->yaw)),
		glm::sin(glm::radians(this->pitch)),
		glm::cos(glm::radians(this->pitch)) * glm::sin(glm::radians(this->yaw))
	));

	this->right = glm::normalize(glm::cross(newFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->up = glm::normalize(glm::cross(right, newFront));
	this->front = newFront;
}


glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getPosition() {
	return this->position;
}

