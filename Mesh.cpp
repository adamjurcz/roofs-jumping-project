#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint>indices, std::vector<Textures>textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	update();
}

void Mesh::draw(ShaderProgram& shader) {
	std::string name;
	vao->bind();

	unsigned int numDiffuse = 1;
	unsigned int numSpecular = 1;
	
	//std::cout << "rozmiar tekstur wektor: " << textures.size() << std::endl;
	
	for (int i = 0; i < textures.size(); i++) {
		std::string num;
		std::string name = textures[i].getLightType();

		if (name == "texture_diffuse") {
			num = std::to_string(numDiffuse++);
		}
		if (name == "texture_specular") {
			num = std::to_string(numSpecular++);
		}

		textures[i].texUnit(shader, (name + num).c_str(), i);
		textures[i].bind();

	}
	
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

	vao->unbind();
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::update() {
	
	this->vao = new VAO();
	this->vao->bind();
	
	VBO vbo = VBO(&vertices.at(0), vertices.size() * sizeof(Vertex));
	EBO ebo = EBO(&indices.at(0), indices.size() * sizeof(GLuint));

	this->vao->linkAttr(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	this->vao->linkAttr(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	this->vao->linkAttr(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	
	this->vao->unbind();
	vbo.unbind();
	ebo.unbind();

}