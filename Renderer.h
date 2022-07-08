#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "ShaderProgram.h"
#include "Textures.h"
#include "WorldTransform.h"
#include "Camera.h"
#include "Skybox.h"
#include "VAO.h"
#include "Model.h"
#include "Skybox.h"
#include "SimpleBuilding.h"



class Renderer
{
private:
	ShaderProgram* lightShader;
	ShaderProgram* blockShader;
	ShaderProgram* tryShader;

	Skybox* skybox;

	std::vector<std::pair<SimpleBuilding*, const char*>> simpleBuildings;

	std::vector<std::pair<Model*, const char*>> models;
	


	
	void initModels();
	void initSimpleShapes();


	void renderTerrain();
	void renderObjects();

	void renderSkyscrapers();

public:
	Renderer();
};



#endif