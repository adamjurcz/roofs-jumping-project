#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "ShaderProgram.h"

class Model {
private:
	std::vector<Mesh> meshes;
	std::vector<Textures> textures;
	std::string path;
	std::string directory;

	void loadModel();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);


public:
	Model(const std::string &path);
	void draw(ShaderProgram& shaderProgram);

};


#endif