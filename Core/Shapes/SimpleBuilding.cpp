#include "SimpleBuilding.h"

SimpleBuilding::SimpleBuilding() {
	vao.bind();
	VBO vbo = VBO(myCube::verticesCube, sizeof(myCube::verticesCube));
	
	vao.linkAttr(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.linkAttr(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();
	
	vbo.unbind();
}

SimpleBuilding::~SimpleBuilding() {
}


void SimpleBuilding::draw(ShaderProgram& shader) {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, myCube::myCubeVertexCount);
	vao.unbind();
}


VAO* SimpleBuilding::getVao() {
	return &vao;
}
