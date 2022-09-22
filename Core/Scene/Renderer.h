#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "../Shaders/ShaderProgram.h"
#include "../World/Skybox.h"
#include "../Models/Model.h"
#include "../Shapes/SimpleBuilding.h"
#include "../Scene/Player.h"
#include "../World/Terrain.h"
#include "../Physics/PhysicCube.h"
#include "Textures.h"

class Renderer
{
private:
	std::unique_ptr<Textures> facadeTexture;
	std::unique_ptr<Textures> leavesTexture;
	std::unique_ptr<Textures> stemTexture;

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

	void renderTree(glm::mat4 proj, glm::mat4 view, glm::mat4 model, Model* treeStem);

	void renderPhysicObject(glm::mat4 proj, glm::mat4 view, glm::mat4 model, PhysicCube* object, Player* player, glm::vec3* lightPos);
};

#endif