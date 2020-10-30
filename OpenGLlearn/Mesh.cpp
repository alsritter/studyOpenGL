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
	/* vector������˳��������ֱ�������ַ���� */
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	// ����λ��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// ���㷨��
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	/*offsetof�ǽṹ���һ��Ԥ����ָ����ĵ�һ������һ���ṹ�壬�ڶ�������������ṹ��Ĳ��� �����᷵���Ǹ�������ṹ��ͷ�����ֽ�ƫ����(Byte Offset)  */
	// ������������
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);//�����0��Ϊ�˽��

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
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);//���һ��������ƫ����
	glBindVertexArray(0);
	
}


