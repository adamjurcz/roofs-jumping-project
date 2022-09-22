#include "Skybox.h"

const float Skybox::skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

const std::vector<std::string> Skybox::cubeFaces = {
	"resources/skybox/right.bmp",
	"resources/skybox/left.bmp",
	"resources/skybox/top.bmp",
	"resources/skybox/bottom.bmp",
	"resources/skybox/front.bmp",
	"resources/skybox/back.bmp" };

Skybox::Skybox() {
	createCubeMap(this->cubeFaces);

	skyboxShader = new ShaderProgram("resources/shaders/v_skybox.glsl", NULL, "resources/shaders/f_skybox.glsl");
	skyboxShader->setInt("skybox", 0);

	float skyboxVert[108];
	std::copy(std::begin(this->skyboxVertices), std::end(this->skyboxVertices), std::begin(skyboxVert));

	VAOskybox = new VAO();
	VAOskybox->bind();
	VBOskybox = new VBO(skyboxVert, sizeof(skyboxVert));
	VAOskybox->linkAttr(*VBOskybox, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	VAOskybox->unbind();
	VBOskybox->unbind();
}

Skybox::~Skybox() {
	delete skyboxShader;
	delete VAOskybox;
	delete VBOskybox;
}

void Skybox::renderSkybox(const glm::mat4& proj, const glm::mat4& view) {
	glDepthMask(GL_FALSE);

	skyboxShader->activate();

	skyboxShader->setMat4("P", proj);
	skyboxShader->setMat4("V", glm::mat4(glm::mat3(view)));


	VAOskybox->bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyboxID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	VAOskybox->unbind();

	glDepthMask(GL_TRUE);
}


void Skybox::createCubeMap(const std::vector<std::string>& cubeFaces) {
		unsigned char* image_data;
		int width, height, channels;

		glGenTextures(1, &skyboxID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

		for (int i = 0; i < 6; i++)
		{
			stbi_set_flip_vertically_on_load(false);
			image_data = stbi_load(cubeFaces[i].c_str(), &width, &height, &channels, 0);

			if (image_data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
				stbi_image_free(image_data);
			}

			else
			{
				std::cout << "Nie udalo sie zaladowac: " << cubeFaces[i];
				stbi_image_free(image_data);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

