#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "ShaderProgram.h"
#include "Skybox.h"
#include "Model.h"
#include "Skybox.h"
#include "SimpleBuilding.h"
#include "Player.h"
#include "Terrain.h"
#include "PhysicCube.h"
#include "Textures.h"

class Renderer
{
private:
	std::unique_ptr<Textures> facadeTexture;

	void initTextures();

public:
	ShaderProgram lightShader;
	ShaderProgram blockShader;
	ShaderProgram tryShader;
	ShaderProgram terrainShader;

	Renderer();

	~Renderer();

	void renderTerrain(glm::mat4 proj, glm::mat4 view, glm::mat4 model, Terrain* terrain, Player* player);

	void renderObjects(glm::mat4 proj, glm::mat4 view, glm::mat4 model, Model* models);

	void renderLightCube(glm::mat4 proj, glm::mat4 view, glm::mat4 model, SimpleBuilding* lightCube);

	void renderPhysicObject(glm::mat4 proj, glm::mat4 view, glm::mat4 model, PhysicCube* object, Player* player, glm::vec3 lightPos);
};

#endif