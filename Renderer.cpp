#include "Renderer.h"

Renderer::Renderer() {
	this->lightShader = new ShaderProgram("v_light_cube.glsl", NULL, "f_light_cube.glsl");
	this->blockShader = new ShaderProgram("v_simple.glsl", NULL, "f_simple.glsl");
	this->tryShader = new ShaderProgram("v_try.glsl", NULL, "f_try.glsl");

	this->skybox = new Skybox();
}

void Renderer::initModels() {
	Model* catModel = new Model("resources/cat/12221_Cat_v1_l3.obj");
	models.push_back(std::make_pair(catModel, "catModel"));
}

void Renderer::initSimpleShapes() {
	Textures* facadeTexture = new Textures("resources/facade.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, "diff");
	SimpleBuilding* skyscraper = new SimpleBuilding(facadeTexture);

	SimpleBuilding* lightShape = new SimpleBuilding();

	simpleBuildings.push_back(std::make_pair(skyscraper, "skyscraper"));
	simpleBuildings.push_back(std::make_pair(lightShape, "lightShape"));
}

void Renderer::renderSkyscrapers() {

}


void Renderer::renderTerrain() {
	
}

void Renderer::renderObjects() {
	
}

