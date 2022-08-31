#ifndef PHYSICCUBE_H
#define PHYSICCUBE_H

#include <iostream>
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/LinearMath/btVector3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Textures.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "PhysicObject.h"


class PhysicCube: public PhysicObject{
private:
	VAO vao;
		
	const static int myCubeVertexCount = 36;
	const static int myCubeArraySize = myCubeVertexCount * 8;

	float verticesCube[myCubeArraySize];
public:
	PhysicCube(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation);
	
	void updateCube(const btVector3& halfSize);

	void draw(ShaderProgram& shader);

	static PhysicCube* createPhysicCube(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation);
};


#endif