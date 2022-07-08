#include "SimpleBuilding.h"

SimpleBuilding::SimpleBuilding(Textures* textures) {
	defaultShader = new ShaderProgram("v_light_cube.glsl", NULL, "f_light_cube.glsl");

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
	delete defaultShader;

}


void SimpleBuilding::simpleBuildingRender(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model, 
	const glm::vec3& lightPos, const glm::vec3& cameraPos, ShaderProgram* shader) {

	ShaderProgram* shaderInUse = shader;

	if (textures != nullptr) {
		textures->bind();
		textures->texUnit(*shaderInUse, "texture0", GL_TEXTURE0);
	}

	shaderInUse->activate();
	
	shaderInUse->setVec3("objectColor", glm::vec3(0.4f, 0.2f, 0.7f));
	shaderInUse->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shaderInUse->setVec3("lightPos", lightPos);
	shaderInUse->setVec3("viewPos", cameraPos);
	

	shaderInUse->setMat4("P", proj);
	shaderInUse->setMat4("V", view);
	shaderInUse->setMat4("M", model);

	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, myCube::myCubeVertexCount);
	vao->unbind();
}

void SimpleBuilding::simpleBuildingRender(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model) {

	ShaderProgram* shaderInUse = defaultShader;

	if (textures != nullptr) {
		textures->bind();
		textures->texUnit(*shaderInUse, "texture0", GL_TEXTURE0);
	}

	shaderInUse->activate();
	shaderInUse->setMat4("P", proj);
	shaderInUse->setMat4("V", view);
	shaderInUse->setMat4("M", model);

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