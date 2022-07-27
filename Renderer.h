#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>
#include <vector>

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


class Renderer
{
public:
	ShaderProgram lightShader;
	ShaderProgram blockShader;
	ShaderProgram tryShader;
	ShaderProgram terrainShader;

	Renderer();

	void renderTerrain(glm::mat4 proj, glm::mat4 view, glm::mat4 model, Terrain* terrain, Player* player);

	void renderObjects(glm::mat4 proj, glm::mat4 view, glm::mat4 model, Model* models);

	void renderSkyscrapers(glm::mat4 proj, glm::mat4 view, glm::mat4 model, SimpleBuilding* simpleBuilding, Player* player, glm::vec3 lightPos);

	void renderLightCube(glm::mat4 proj, glm::mat4 view, glm::mat4 model, SimpleBuilding* lightCube);
};



#endif