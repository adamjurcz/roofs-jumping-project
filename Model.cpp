#include "Model.h"

Model::Model(const std::string& path) {
	this->path = path;
	loadModel();
}

void Model::draw(ShaderProgram& shaderProgram) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shaderProgram);
    }
}

void Model::loadModel() {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(this->path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene) {
		std::cout << "Blad importowania" << std::endl;
		return;
	}
    
    this->directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Textures> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        //
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.pos = vector;
        //
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        //
        if (mesh->mTextureCoords[0]) 
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord = vec;
        }
        else {
            vertex.texCoord = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    // process indices
    
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    // process material
    
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Textures> diffuse;
        

        for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
            aiString file;
            material->GetTexture(aiTextureType_DIFFUSE, i, &file);

            std::string fileDirectory = directory + '/' + file.C_Str();

            Textures loadedTexture = Textures(fileDirectory.c_str(), GL_TEXTURE_2D, GL_TEXTURE0 + i, GL_RGB, "texture_diffuse");
            diffuse.push_back(loadedTexture);
        }

        textures.insert(textures.end(), diffuse.begin(), diffuse.end());
    }
    
    
    return Mesh(vertices, indices, textures);
}
