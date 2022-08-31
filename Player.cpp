#include "Player.h"

Player::Player(GLFWwindow* window, unsigned int _WIDTH, unsigned int _HEIGHT, glm::vec3 startPosition): camera(startPosition, _WIDTH, _HEIGHT){
	position = startPosition;
	_MOVABLE_HEIGHT = startPosition.y;
	_SPEED = 10.0f;
	_GRAVITY = -10.0f;
	_JUMP = 10.0f;
}

void Player::keyboardUpdate(GLFWwindow* window, ObjectsManager& objectsManager, float deltaTime) {
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

void Player::mouseUpdate(GLFWwindow* window, ObjectsManager& objectsManager, float deltaTime) {
	double mXpos, mYpos;
	glfwGetCursorPos(window, &mXpos, &mYpos);
	camera.mouseMove(mXpos, mYpos, deltaTime);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		shootBox(objectsManager);
	}

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


void Player::shootBox(ObjectsManager& objectsManager) {
	glm::vec3 velocity = camera.getFront();
	velocity = glm::normalize(velocity);
	velocity *= 50.0f;

	objectsManager.addShootedCube(btVector3(0.5f, 0.5f, 0.5f), 1.0f, btVector3(0.5f, 0.5f, 0.5f), Maths::vec3ToBtVector3(&camera.getPosition()),
		btQuaternion(0, 0, 0, 1), Maths::vec3ToBtVector3(&velocity));
}

glm::vec3 Player::jump() {
	camera.setJumpPower(_JUMP);
	glm::vec3 dist = camera.getJumpPower() * glm::vec3(0.0f, 1.0f, 0.0f);
	return dist;
}

glm::vec3 Player::getPickRay(GLFWwindow* window) {
	double mXpos, mYpos;
	
	int _WIDTH, _HEIGHT;
	glfwGetWindowSize(window, &_WIDTH, &_HEIGHT);

	const glm::mat4 projMatrix = camera.getProjMatrix();
	const glm::mat4 viewMatrix = camera.getViewMatrix();

	glfwGetCursorPos(window, &mXpos, &mYpos);

	glm::vec2 normalizedVec = getNormalizedCoords(mXpos, mYpos, _WIDTH, _HEIGHT);

	glm::vec4 directedVec = glm::vec4(normalizedVec.x, normalizedVec.y, -1.0f, 1.0f);

	glm::vec4 rayEye = glm::inverse(projMatrix) * directedVec;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

	glm::vec3 rayWorld = glm::inverse(viewMatrix) * rayEye; //schodzimy o jeden wymiar

	rayWorld = glm::normalize(rayWorld);
	return rayWorld;
}

glm::vec2 Player::getNormalizedCoords(double x, double y, int _WIDTH, int _HEIGHT) {
	float normalizedX = (static_cast<float>(x) * 2.0f) / static_cast<float>(_WIDTH) - 1.0f;
	float normalizedY = 1.0f - (static_cast<float>(y) * 2.0f) / static_cast<float>(_HEIGHT);

	glm::vec2 normalizedVec = glm::vec2(normalizedX, normalizedY);
	return normalizedVec;

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