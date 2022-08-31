#include "Renderer.h"

Renderer::Renderer() : lightShader("v_light_cube.glsl", NULL, "f_light_cube.glsl"), 
			blockShader("v_simple.glsl", NULL, "f_simple.glsl"),
			tryShader("v_try.glsl", NULL, "f_try.glsl"), 
			terrainShader("v_terrain.glsl", NULL, "f_terrain.glsl") {
	initTextures();
}

Renderer::~Renderer() {

}

void Renderer::renderTerrain(glm::mat4 proj, glm::mat4 view, glm::mat4 model, Terrain* terrain, Player* player) {
	terrainShader.activate();
	terrainShader.setMat4("P", proj);
	terrainShader.setMat4("V", view);
	terrainShader.setMat4("M", model);

	terrain->terrainRender(terrainShader, player->position, player->camera.getFar());
}


void Renderer::renderObjects(glm::mat4 proj, glm::mat4 view, glm::mat4 model, Model* models) {
	
	tryShader.activate();
	tryShader.setMat4("P", proj);
	tryShader.setMat4("V", view);
	tryShader.setMat4("M", model);

	models->draw(tryShader);
	
}

void Renderer::renderLightCube(glm::mat4 proj, glm::mat4 view, glm::mat4 model, SimpleBuilding* lightCube) {
	lightShader.activate();
	lightShader.setMat4("P", proj);
	lightShader.setMat4("V", view);
	lightShader.setMat4("M", model);

	lightCube->draw(lightShader);
}

void Renderer::renderPhysicObject(glm::mat4 proj, glm::mat4 view, glm::mat4 model, PhysicCube* object, Player* player, glm::vec3 lightPos) {
	blockShader.activate();
	blockShader.setMat4("P", proj);
	blockShader.setMat4("V", view);
	blockShader.setMat4("M", model);

	blockShader.setVec3("objectColor", glm::vec3(0.4f, 0.2f, 0.7f));
	blockShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	blockShader.setVec3("lightPos", lightPos);
	blockShader.setVec3("viewPos", player->position);
	blockShader.setVec3("sunDirect", glm::vec3(-0.3f, -1.0f, -0.4f));

	facadeTexture->bind();
	facadeTexture->texUnit(blockShader, "texture0", 0);
	object->draw(tryShader);
}

void Renderer::initTextures() {
	facadeTexture.reset(new Textures("resources/facade.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, "diff"));
}


/*
#include "TexturesHandler.h"

TexturesHandler::TexturesHandler(): texturesNum(0) {
	Textures* facadeTexture = new Textures("resources/facade.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, "diff"); //1
	texturesMap[1] = facadeTexture;
}

TexturesHandler::~TexturesHandler() {
	std::map<unsigned int, Textures*>::iterator it;
	for (it = texturesMap.begin(); it != texturesMap.end(); it++) {
		delete it->second;
	}
	texturesMap.clear();
}

*/
