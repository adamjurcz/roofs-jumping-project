#include "PhysicCube.h"

PhysicCube::PhysicCube(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation):
			PhysicObject(new btBoxShape(size), mass, color, initialPosition, initialRotation){
	
	const btBoxShape* box = static_cast<const btBoxShape*>(this->GetShape());
	btVector3 halfSize = box->getHalfExtentsWithMargin();

	updateCube(halfSize);

	vao.bind();
	VBO vbo = VBO(verticesCube, sizeof(verticesCube));

	vao.linkAttr(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.linkAttr(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.linkAttr(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.unbind();
	vbo.unbind();
}




void PhysicCube::updateCube(const btVector3& halfSize) {
	float halfWidth = halfSize.x();
	float halfHeight = halfSize.y();
	float halfDepth = halfSize.z();

	float divSquare = (halfHeight / halfWidth);

	glm::vec3 vertices[8] =
	{
		glm::vec3(-halfWidth, -halfHeight, -halfDepth), // (-, -, -) 0
		glm::vec3(halfWidth, -halfHeight, -halfDepth), //(+, -, -) 1
		glm::vec3(halfWidth, halfHeight, -halfDepth),  //(+, +, -) 2
		glm::vec3(-halfWidth, halfHeight, -halfDepth), //(-, +, -) 3
		glm::vec3(-halfWidth, -halfHeight, halfDepth), //(-, -, +) 4
		glm::vec3(halfWidth, -halfHeight, halfDepth),  //(+, -, +) 5
		glm::vec3(halfWidth, halfHeight, halfDepth),  //(+, +, +) 6
		glm::vec3(-halfWidth, halfHeight, halfDepth) //(-, +, +) 7
	};

	static int indices[36] =
	{
		0, 4, 7, 2, 0, 3,
		5, 0, 1, 2, 1, 0,
		0, 7, 3, 5, 4, 0,
		7, 4, 5, 6, 1, 2,
		1, 6, 5, 6, 2, 3,
		6, 3, 7, 6, 7, 5
	};

	glm::vec2 texCoords[4] =
	{
		glm::vec2(0.0f, 0.0f), //0 0 -> 0
		glm::vec2(1.0f, 0.0f), //1 0 -> 1
		glm::vec2(1.0f, divSquare), //1 1 -> 2
		glm::vec2(0.0f, divSquare)  //0 1 -> 3
	};

	/* prawdziwe indeksy teksturowania
	static int texIndices[36] = 
	{
		0, 1, 2, 3, 1, 2,
		0, 2, 3, 3, 0, 1,
		0, 2, 3, 0, 1, 2,
		3, 0, 1, 3, 1, 2,
		1, 3, 0, 1, 2, 3,
		1, 3, 0, 2, 3, 1

	};
	*/
	static int texIndices[36] =
	{
		0, 1, 2, 3, 1, 2,
		0, 2, 3, 3, 0, 1,
		0, 2, 3, 0, 1, 2,
		3, 0, 1, 3, 1, 2,
		1, 3, 0, 0, 0, 0,
		0, 0, 0, 2, 3, 1

	};


	for (int i = 0; i < 36; i++) {
		verticesCube[i * 8 + 0] = vertices[indices[i]].x;
		verticesCube[i * 8 + 1] = vertices[indices[i]].y;
		verticesCube[i * 8 + 2] = vertices[indices[i]].z;
		if ((i + 1) % 3 == 0) {
			glm::vec3 a = glm::vec3(verticesCube[(i - 2) * 8 + 0], verticesCube[(i - 2) * 8 + 1], verticesCube[(i - 2) * 8 + 2]);
			glm::vec3 b = glm::vec3(verticesCube[(i - 1) * 8 + 0], verticesCube[(i - 1) * 8 + 1], verticesCube[(i - 1) * 8 + 2]);
			glm::vec3 c = glm::vec3(verticesCube[(i - 0) * 8 + 0], verticesCube[(i - 0) * 8 + 1], verticesCube[(i - 0) * 8 + 2]);
			glm::vec3 crossProd = glm::cross((a - b), (a - c));
			glm::vec3 normal = glm::normalize(crossProd);

			verticesCube[(i - 2) * 8 + 3] = normal.x;
			verticesCube[(i - 2) * 8 + 4] = normal.y;
			verticesCube[(i - 2) * 8 + 5] = normal.z;

			verticesCube[(i - 1) * 8 + 3] = normal.x;
			verticesCube[(i - 1) * 8 + 4] = normal.y;
			verticesCube[(i - 1) * 8 + 5] = normal.z;

			verticesCube[(i - 0) * 8 + 3] = normal.x;
			verticesCube[(i - 0) * 8 + 4] = normal.y;
			verticesCube[(i - 0) * 8 + 5] = normal.z;
		}

		verticesCube[i * 8 + 6] = texCoords[texIndices[i]].x;
		verticesCube[i * 8 + 7] = texCoords[texIndices[i]].y;
	}
	/* ->do debugowania
	std::cout << "--------------------------------------" << std::endl;
	for (int i = 0; i < 36; i++) {
		std::cout << verticesCube[i * 8 + 0] << "  " << verticesCube[i * 8 + 1] <<"  "<< verticesCube[i * 8 + 2] <<"\t\t"<< verticesCube[i * 8 + 3] <<"  "<< verticesCube[i * 8 + 4] <<"  "<< verticesCube[i * 8 + 5] << "\t\t"
			<< verticesCube[i * 8 + 6] <<" "<< verticesCube[i * 8 + 7] << std::endl;
	}
	std::cout << "----------------------------------------" << std::endl;
	*/
}

void PhysicCube::draw(ShaderProgram& shader) {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);
	vao.unbind();
}

PhysicCube* PhysicCube::createPhysicCube(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation) {
	PhysicCube* obj = new PhysicCube(size, mass, color, initialPosition, initialRotation);
	return obj;
}

