#include "SimpleBuilding.h"

SimpleBuilding::SimpleBuilding(Textures* textures) {
	vao = new VAO();
	vao->bind();
	VBO vbo = VBO(myCube::verticesCube, sizeof(myCube::verticesCube));
	
	vao->linkAttr(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao->linkAttr(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao->linkAttr(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vao->unbind();
	
	vbo.unbind();

	if (textures != nullptr) {
		this->textures = textures;
	}
}

SimpleBuilding::~SimpleBuilding() {
	delete vao;
	if (textures != nullptr) {
		delete textures;
	}
}


void SimpleBuilding::draw(ShaderProgram& shader) {
	if (textures != nullptr) {
		textures->bind();
		textures->texUnit(shader, "texture0", GL_TEXTURE0);
	}

	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, myCube::myCubeVertexCount);
	vao->unbind();
}


VAO* SimpleBuilding::getVao() {
	return vao;
}

Textures* SimpleBuilding::getTextures() {
	return textures;
}