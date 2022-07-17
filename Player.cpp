#include "Player.h"
Player::Player(): camera(startPosition, _WIDTH, _HEIGHT){

}

void Player::keyboardUpdate(GLFWwindow* window, float deltaTime) {
	camera.setSpeed(static_cast<float>(deltaTime * 15));
	glm::vec3 oldPos = camera.getPosition();
	float oldY = camera.getPosition().y;

	glm::vec3 newPos;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += camera.getSpeed()* glm::normalize(glm::vec3(camera.getFront().x, 0, camera.getFront().z));
		camera.setPosition(position);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += camera.getSpeed() * (-glm::normalize(glm::vec3(camera.getFront().x, 0, camera.getFront().z)));
		camera.setPosition(position);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += camera.getSpeed() * -glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
		camera.setPosition(position);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += camera.getSpeed() * glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
		camera.setPosition(position);
	}
	this->position = camera.getPosition();
}

void Player::mouseUpdate(GLFWwindow* window, float deltaTime) {
	double mXpos, mYpos;
	glfwGetCursorPos(window, &mXpos, &mYpos);
	camera.mouseMove(mXpos, mYpos, deltaTime);
}

/*
camera.setSpeed(static_cast<float>(deltaTime * 3.4));
glm::vec3 oldPos = camera.getPosition();
float oldY = camera.getPosition().y;

glm::vec3 newPos;

if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
{
	//position += camera.getSpeed() * (-glm::cross(camera.getRight(), camera.getUp()));
	//newPos = glm::vec3(position.x, oldY, position.z);
	position += glm::normalize(camera.getSpeed() * glm::vec3(camera.getFront().x, 0, camera.getFront().z));
	camera.setPosition(position);
}
if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
{
	position += camera.getSpeed() * glm::cross(camera.getRight(), camera.getUp());
	camera.setPosition(position);
}
if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
{
	position += camera.getSpeed() * -glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
	camera.setPosition(position);
}
if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
{
	position += camera.getSpeed() * glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
	camera.setPosition(position);
}
this->position = camera.getPosition();
*/