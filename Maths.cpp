#include "Maths.h"

bool Maths::checkIfInsideRectangle(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 P) {
	glm::vec2 ABvec = vectorAB(A, B);
	glm::vec2 BCvec = vectorAB(B, C);
	glm::vec2 APvec = vectorAB(A, P);
	glm::vec2 BPvec = vectorAB(B, P);

	float ABAPdot = dotProduct(ABvec, APvec);
	float ABABdot = dotProduct(ABvec, ABvec);
	float BCBPdot = dotProduct(BCvec, BPvec);
	float BCBCdot = dotProduct(BCvec, BCvec);

	if (0 <= ABAPdot && ABAPdot <= ABABdot && 0 <= BCBPdot && BCBPdot <= BCBCdot) return 1;
	return 0;
}

float Maths::dotProduct(glm::vec2 A, glm::vec2 B)
{
	return A.x * B.x + A.y * B.y;
}

glm::vec2 Maths::vectorAB(glm::vec2 A, glm::vec2 B)
{
	return glm::vec2(B.x - A.x, B.y - A.y);
}

glm::mat4 Maths::btScalarToMat4(btScalar* matrix) {
	return glm::mat4(
		matrix[0], matrix[1], matrix[2], matrix[3],
		matrix[4], matrix[5], matrix[6], matrix[7],
		matrix[8], matrix[9], matrix[10], matrix[11],
		matrix[12], matrix[13], matrix[14], matrix[15]);
}

glm::vec3 Maths::btVector3ToVec3(btVector3* btVector3) {
	return glm::vec3(btVector3->getX(), btVector3->getY(), btVector3->getZ());
}

btVector3 Maths::vec3ToBtVector3(glm::vec3* vec3) {
	return btVector3(vec3->x, vec3->y, vec3->z);
}