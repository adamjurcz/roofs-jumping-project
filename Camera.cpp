#include "Camera.h"
Camera::Camera(glm::vec3 position, int windowWidth, int windowHeight) {
	this->position = position;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	this->lastMouseX = static_cast<float>(this->windowWidth / 2);
	this->lastMouseY = static_cast<float>(this->windowHeight / 2);

	this->fov = 45.0f;
	this->aspect = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	this->zFar = 200.0f;
	this->zNear = 0.1f;

	updateVectors();
	updateView();
	updateProj();
}



void Camera::mouseMove(double mouseX, double mouseY, double deltaTime) {
	mouseY = -mouseY;
	if (this->_firstClick == true) {
		this->lastMouseX = mouseX;
		this->lastMouseY = mouseY;
		this->_firstClick = false;
	}
	float xOffset = (static_cast<float>(mouseX) - this->lastMouseX) * this->_sensivity * static_cast<float>(deltaTime);
	float yOffset = (static_cast<float>(mouseY) - this->lastMouseY) * this->_sensivity * static_cast<float>(deltaTime);

	this->lastMouseX = mouseX;
	this->lastMouseY = mouseY;

	this->_yaw += xOffset;
	this->_pitch += yOffset;

	if (this->_pitch > 89.0f) {
		this->_pitch = 89.0f;
	}
	if (this->_pitch < -89.0f) {
		this->_pitch = -89.0f;
	}
	
	updateVectors();
	updateView();
}

void Camera::updateVectors() {
	glm::vec3 newFront = glm::normalize(glm::vec3(
		glm::cos(glm::radians(this->_pitch)) * glm::cos(glm::radians(this->_yaw)),
		glm::sin(glm::radians(this->_pitch)),
		glm::cos(glm::radians(this->_pitch)) * glm::sin(glm::radians(this->_yaw))
	));

	this->right = glm::normalize(glm::cross(newFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->up = glm::normalize(glm::cross(right, newFront));
	this->front = newFront;
}

void Camera::updateView() {
	this->view = glm::lookAt(position, position + front, up);
}

void Camera::updateProj() {
	this->proj = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::setPosition(glm::vec3& position) {
	this->position = position;

	updateView();
}

void Camera::setProjMatrix(float fov, float aspect, float zNear, float zFar) {
	this->fov = fov;
	this->aspect = aspect;
	this->zNear = zNear;
	this->zFar = zFar;

	updateProj();
}

void Camera::setFov(float fov) {
	this->fov = fov;

	updateProj();
}

void Camera::setAspect(float aspect) {
	this->aspect = aspect;

	updateProj();
}

void Camera::setNear(float zNear) {
	this->zNear = zNear;

	updateProj();
}


void Camera::setFar(float zFar) {
	this->zFar = zFar;

	updateProj();
}

void Camera::setSensivity(float sensivity) {
	this->_sensivity = sensivity;
}

void Camera::setSpeed(float speed) {
	this->_pSpeed = speed;
}

void Camera::setAcceleration(float acceleration) {
	this->_acceleration = acceleration;
}

void Camera::setGravity(float gravity) {
	this->_gravity = gravity;
}

void Camera::setJumpPower(float jumpPower) {
	this->_jumpPower = jumpPower;
}


float Camera::getFov() {
	return fov;
}

float Camera::getAspect() {
	return aspect;
}

float Camera::getNear() {
	return zNear;
}
float Camera::getFar() {
	return zFar;
}


float Camera::getSensivity() {
	return _sensivity;
}

float Camera::getSpeed() {
	return _pSpeed;
}

float Camera::getAcceleration() {
	return _acceleration;
}

float Camera::getGravity() {
	return _gravity;
}

float Camera::getJumpPower() {
	return _jumpPower;
}




glm::mat4& Camera::getProjMatrix() {
	return proj;
}

glm::mat4& Camera::getViewMatrix() {
	return view;
}

glm::vec3& Camera::getPosition() {
	return position;
}

glm::vec3& Camera::getFront() {
	return front;
}

glm::vec3& Camera::getUp() {
	return up;
}

glm::vec3& Camera::getRight() {
	return right;
}

