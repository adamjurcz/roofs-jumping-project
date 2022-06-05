#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class WorldTransform
{
private:
	glm::vec3 wscale = glm::vec3(1.0f);
	glm::vec3 wrotation = glm::vec3(0.0f);
	glm::vec3 wtranslation = glm::vec3(0.0f);
	float wangle = 0.0f;

public:
	void setScale(glm::vec3 scale);
	void setRotation(glm::vec3 rotation, float angle = 0.0f);
	void setTranslation(glm::vec3 translation);

	glm::mat4 getWorld();
};

