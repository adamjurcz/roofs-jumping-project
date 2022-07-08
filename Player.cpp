#include "Player.h"
Player::Player(): camera(startPosition, _WIDTH, _HEIGHT){

}

void Player::keyboardUpdate(GLFWwindow* window, float deltaTime) {
	camera.setSpeed(static_cast<float>(deltaTime * 3.4));
	glm::vec3 oldPos = camera.getPosition();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += camera.getSpeed() * camera.getFront();
		camera.setPosition(position);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += camera.getSpeed() * -glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
		camera.setPosition(position);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += camera.getSpeed() * -camera.getFront();
		camera.setPosition(position);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += camera.getSpeed() * glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
		camera.setPosition(position);
	}

	if (oldPos != camera.getPosition()) {

	}

	this->position = camera.getPosition();
}

void Player::mouseUpdate(GLFWwindow* window, float deltaTime) {
	double mXpos, mYpos;
	glfwGetCursorPos(window, &mXpos, &mYpos);
	camera.mouseMove(mXpos, mYpos, deltaTime);
}


