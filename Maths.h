#ifndef MATHS_H
#define MATHS_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/LinearMath/btVector3.h>

class Maths {
public:
	static bool checkIfInsideRectangle(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 P);
	static float dotProduct(glm::vec2 A, glm::vec2 B);
	static glm::vec2 vectorAB(glm::vec2 A, glm::vec2 B);
	
	static glm::mat4 btScalarToMat4(btScalar* matrix);
	static glm::vec3 btVector3ToVec3(btVector3* btvector3);
	static btVector3 vec3ToBtVector3(glm::vec3* vec3);
};



#endif