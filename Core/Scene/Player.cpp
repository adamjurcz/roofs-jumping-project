#include "Player.h"

Player::Player(GLFWwindow* window, unsigned int _WIDTH, unsigned int _HEIGHT, glm::vec3 startPosition): camera(startPosition, _WIDTH, _HEIGHT){
	this->startPosition = startPosition;
	position = startPosition;
	_MOVABLE_HEIGHT = 63.0f;
	_SPEED = 10.0f;
	_GRAVITY = -10.0f;
	_JUMP = 70.0f;
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
	
	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && (isStable) || jumpState > 0){
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
	if (isStable) {
		position.y = _MOVABLE_HEIGHT;
	}

	camera.setPosition(position);
	position = camera.getPosition();
}


void Player::shootBox(ObjectsManager& objectsManager) {
	glm::vec3 velocity = camera.getFront();
	velocity = glm::normalize(velocity);
	velocity *= 50.0f;

	objectsManager.addShootedCube(btVector3(0.5f, 0.5f, 0.5f), 1.0f, btVector3(0.5f, 0.5f, 0.5f), Maths::vec3ToBtVector3(&camera.getPosition()),
		btQuaternion(0, 0, 0, 1), Maths::vec3ToBtVector3(&velocity));
}


glm::vec3 Player::jump() {
	if (jumpState == 0) jumpState = 5;
	float jumpPower = pow(camera.getJumpPower(), jumpState);
	jumpState--;

	glm::vec3 velocity = jumpPower * glm::vec3(0.0f, 1.0f, 0.0f);
	return velocity;
}

void Player::checkStability(ObjectsManager& objectsManager) {
	const float lowerBound = 0.01f;
	const float upperBound = 3.2f;

	glm::vec3 up = glm::vec3(0.0f, 10000.0f, 0.0f);
	glm::vec3 down = -up;

	btVector3 output;
	btVector3 normal;
	
	//wziac pod uwage normalna 0 1 0 i odleglosc 0.1<x<3.1 x- odleglosc od ziemi
	if (objectsManager.raycast(Maths::vec3ToBtVector3(&position), Maths::vec3ToBtVector3(&down), output, normal)) {
		glm::vec3 positionObjectVec = position - Maths::btVector3ToVec3(&output);
		float length = glm::length(positionObjectVec);
		std::cout << "\nOdleglosc od obiektu z dolu: " << length << " Wektor w dol: " << positionObjectVec.x << " " << positionObjectVec.y << " " << positionObjectVec.z << " NORMALNA: "
			<< normal.getX() << " " << normal.getY() << " " << normal.getZ();

		std::cout << "\n----------------";
		if (length < upperBound && length > lowerBound && normal.getX() < 0.05f && normal.getY() > 0.95f && normal.z() < 0.05f) {
			this->isStable = true;
			return;
		}
	}
	this->isStable = false;
}
