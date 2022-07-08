#ifndef SIMPLEBUILDING_H
#define SIMPLEBUILDING_H

#include "ShaderProgram.h"
#include "Textures.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "myCube.h"

class SimpleBuilding {
private:
	VAO* vao;
	Textures* textures;
	ShaderProgram* defaultShader;

public:
	SimpleBuilding(Textures* textures = nullptr);
	~SimpleBuilding();

	void simpleBuildingRender(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model, 
		const glm::vec3& cameraPos, const glm::vec3& lightPos, ShaderProgram* shader);

	void simpleBuildingRender(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model);


	VAO* getVao();
	Textures* getTextures();
};

#endif