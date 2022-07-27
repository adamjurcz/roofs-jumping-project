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
	glm::mat4 proj;
	glm::mat4 view;

	int windowWidth, windowHeight;

	float lastMouseX;
	float lastMouseY;
	float zNear;
	float zFar;
	float aspect;
	float fov;


	float _sensivity = 10.0f;
	float _pSpeed = 0.0f;
	float _acceleration = 0.0f;
	float _gravity = 0.0f;
	float _jumpPower = 0.0f;

	float _yaw = 0.0f;
	float _pitch = 0.0f;

	bool _firstClick = true;

	void updateVectors();
	void updateProj();
	void updateView();


public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	Camera(glm::vec3 position, int windowWidth, int windowHeight);

	void mouseMove(double mouseX, double mouseY, double deltaTime);

	void setPosition(glm::vec3& pos);

	void setProjMatrix(float fov, float aspect, float zNear, float zFar);
	void setFov(float fov);
	void setAspect(float aspect);
	void setNear(float zNear);
	void setFar(float zFar);


	void setSensivity(float sensivity);
	void setSpeed(float speed);
	void setAcceleration(float acceleration);
	void setGravity(float gravity);
	void setJumpPower(float jumpPower);


	float getFov();
	float getAspect();
	float getNear();
	float getFar();

	float getSensivity();
	float getSpeed();
	float getAcceleration();
	float getGravity();
	float getJumpPower();



	glm::mat4& getProjMatrix();
	glm::mat4& getViewMatrix();
	glm::vec3& getPosition();

	glm::vec3& getFront();
	glm::vec3& getUp();
	glm::vec3& getRight();


};

#endif