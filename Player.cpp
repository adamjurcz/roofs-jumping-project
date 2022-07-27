#include "Player.h"
Player::Player(unsigned int _WIDTH, unsigned int _HEIGHT, glm::vec3 startPosition): camera(startPosition, _WIDTH, _HEIGHT){
	position = startPosition;
	_MOVABLE_HEIGHT = startPosition.y;
	_SPEED = 10.0f;
	_GRAVITY = -10.0f;
	_JUMP = 10.0f;
}

void Player::keyboardUpdate(GLFWwindow* window, float deltaTime) {
	camera.setSpeed(deltaTime * _SPEED);
	camera.setJumpPower(deltaTime * _JUMP);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		position += camera.getSpeed()* glm::normalize(glm::vec3(camera.getFront().x, 0, camera.getFront().z));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		position += camera.getSpeed() * (-glm::normalize(glm::vec3(camera.getFront().x, 0, camera.getFront().z)));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		position += camera.getSpeed() * -glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		position += camera.getSpeed() * glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
	}
	
	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && (isStable)){
		position += jump();
		isStable = false;
	}
	
	camera.setPosition(position);
	this->position = camera.getPosition();
}

void Player::mouseUpdate(GLFWwindow* window, float deltaTime) {
	double mXpos, mYpos;
	glfwGetCursorPos(window, &mXpos, &mYpos);
	camera.mouseMove(mXpos, mYpos, deltaTime);
}

void Player::gravityUpdate(float deltaTime) {
	camera.setGravity(deltaTime * _GRAVITY);
	position += camera.getGravity() * glm::vec3(0.0f, 1.0f, 0.0f);
	if (position.y < _MOVABLE_HEIGHT) {
		position.y = _MOVABLE_HEIGHT;
		isStable = true;
	}
	camera.setPosition(position);
	this->position = camera.getPosition();
}

glm::vec3 Player::jump() {
	camera.setJumpPower(_JUMP);
	glm::vec3 dist = camera.getJumpPower() * glm::vec3(0.0f, 1.0f, 0.0f);
	return dist;
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