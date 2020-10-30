#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>
#include <vector>
#include "Mesh.h"
#include "Shader.h"


class Model
{
public:
	Model(std::string const &path);
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;//����exe�ļ�ͬ��·��
	void Draw(Shader* shader);
	~Model();
private:

	void loadModel(std::string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory);
};

