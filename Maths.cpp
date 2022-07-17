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
