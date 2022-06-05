#include "WorldTransform.h"

void WorldTransform::setScale(glm::vec3 scale) {
	wscale.x = scale.x;
	wscale.y = scale.y;
	wscale.z = scale.z;
}

void WorldTransform::setRotation(glm::vec3 rotation, float angle) {
	wrotation.x = rotation.x;
	wrotation.y = rotation.y;
	wrotation.z = rotation.z;
	
	wangle = angle;
}

void WorldTransform::setTranslation(glm::vec3 translation) {
	wtranslation.x = translation.x;
	wtranslation.y = translation.y;
	wtranslation.z = translation.z;
}

glm::mat4 WorldTransform::getWorld() {
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), wscale);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), wangle, wrotation);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), wtranslation);

	glm::mat4 worldTransformation = translationMatrix * rotationMatrix * scaleMatrix;
	return worldTransformation;
}