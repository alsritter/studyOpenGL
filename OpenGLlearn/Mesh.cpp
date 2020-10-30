#include "Mesh.h"



Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures)
	:vertices(_vertices),indices(_indices),textures(_textures)
{
	setupMesh();

}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/* vector容器是顺序容器，直接物理地址相连 */
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	// 顶点位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// 顶点法线
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	/*offsetof是结构体的一个预处理指令，它的第一参数是一个结构体，第二个参数是这个结构体的参数 这个宏会返回那个变量距结构体头部的字节偏移量(Byte Offset)  */
	// 顶点纹理坐标
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);//这里绑定0是为了解绑

}



Mesh::~Mesh()
{
}

void Mesh::Draw(Shader * shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		if (textures[i].type == "texture_diffuse")
		{
			diffuseNr++;
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		else if (textures[i].type == "texture_specular")
		{
			specularNr++;
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		shader->SetInt("material." + textures[i].type + std::to_string(textures[i].id), i);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);//最后一个参数是偏移量
	glBindVertexArray(0);
	
}


