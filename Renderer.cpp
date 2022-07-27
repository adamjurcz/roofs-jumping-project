#include "Renderer.h"

Renderer::Renderer() : lightShader("v_light_cube.glsl", NULL, "f_light_cube.glsl"), blockShader("v_simple.glsl", NULL, "f_simple.glsl"),
			tryShader("v_try.glsl", NULL, "f_try.glsl"), terrainShader("v_terrain.glsl", NULL, "f_terrain.glsl") {
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

void Renderer::renderSkyscrapers(glm::mat4 proj, glm::mat4 view, glm::mat4 model, SimpleBuilding* simpleBuilding, Player* player, glm::vec3 lightPos) {
	blockShader.activate();

	blockShader.setVec3("objectColor", glm::vec3(0.4f, 0.2f, 0.7f));
	blockShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	blockShader.setVec3("lightPos", lightPos);
	blockShader.setVec3("viewPos", player->position);

	blockShader.setMat4("P", proj);
	blockShader.setMat4("V", view);
	blockShader.setMat4("M", model);

	simpleBuilding->draw(blockShader);
}

void Renderer::renderLightCube(glm::mat4 proj, glm::mat4 view, glm::mat4 model, SimpleBuilding* lightCube) {
	lightShader.activate();
	lightShader.setMat4("P", proj);
	lightShader.setMat4("V", view);
	lightShader.setMat4("M", model);

	lightCube->draw(lightShader);
}




