#ifndef MATHS_H
#define MATHS_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Maths {
public:
	static bool checkIfInsideRectangle(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 P);
	static float dotProduct(glm::vec2 A, glm::vec2 B);
	static glm::vec2 vectorAB(glm::vec2 A, glm::vec2 B);
};



#endif