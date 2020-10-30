#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <gl/glew.h>
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	/* 这个id就是图像索引 */
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh
{
public:
	/* Vertex data */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> _vertices,std::vector<unsigned int> _indices,std::vector<Texture> _textures);
	~Mesh();
	void Draw(Shader* shader);
private:
	unsigned VAO, VBO, EBO;
	void setupMesh();
};

