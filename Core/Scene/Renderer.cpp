#include "Renderer.h"

Renderer::Renderer() : lightShader("resources/shaders/v_light_cube.glsl", NULL, "resources/shaders/f_light_cube.glsl"), 
			blockShader("resources/shaders/v_simple.glsl", NULL, "resources/shaders/f_simple.glsl"),
			tryShader("resources/shaders/v_try.glsl", NULL, "resources/shaders/f_try.glsl"), 
			terrainShader("resources/shaders/v_terrain.glsl", NULL, "resources/shaders/f_terrain.glsl") {
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

void Renderer::renderTree(glm::mat4 proj, glm::mat4 view, glm::mat4 model, Model* treeStem) {
	tryShader.activate();
	tryShader.setMat4("P", proj);
	tryShader.setMat4("V", view);
	tryShader.setMat4("M", model);

	stemTexture->texUnit(tryShader, "texture_diffuse0", 0);
	treeStem->draw(tryShader);
}

void Renderer::renderPhysicObject(glm::mat4 proj, glm::mat4 view, glm::mat4 model, PhysicCube* object, Player* player, glm::vec3* lightPos) {
	blockShader.activate();
	blockShader.setMat4("P", proj);
	blockShader.setMat4("V", view);
	blockShader.setMat4("M", model);

	blockShader.setVec3("objectColor", glm::vec3(0.4f, 0.2f, 0.7f));
	blockShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	blockShader.setVec3("lightPos[0]", lightPos[0]);
	blockShader.setVec3("lightPos[1]", lightPos[1]);

	blockShader.setVec3("viewPos", player->position);
	blockShader.setVec3("sunDirect", glm::vec3(-0.3f, -1.0f, -0.4f));

	facadeTexture->texUnit(blockShader, "texture0", 0);
	object->draw(tryShader);
	facadeTexture->unbind();
}

void Renderer::initTextures() {
	facadeTexture.reset(new Textures("resources/walls/facade.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, "diff"));
	leavesTexture.reset(new Textures("resources/tree/maple_leaf.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, "diff"));
	stemTexture.reset(new Textures("resources/tree/maple_bark.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, "diff"));

}

