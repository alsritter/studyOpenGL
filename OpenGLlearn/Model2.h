
#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>
#include <vector>
#include "Mesh2.h"
#include "Shader.h"

class Model2
{
public:
	/*  Model Data */
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh2> meshes;
	std::string directory;
	bool gammaCorrection;

	Model2(std::string const &path, bool gamma = false);
	~Model2();
	void Draw(Shader shader);


private:

	void loadModel(std::string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh2 processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);

};

