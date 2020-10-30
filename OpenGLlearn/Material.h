#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Material
{
public:
	Material( glm::vec3 _diffuse , glm::vec3 _specular ,float _shininess, float _metallic , float _Gloss);
	/*������*/
	glm::vec3 diffuse ;
	/*���淴��*/
	glm::vec3 specular ;
	/*�����*/
	float gloss = 20;
	/*������*/
	float metallic = 0.1f;
	/*ƽ����*/
	float Smoothness = 0.1f;


	~Material();

};

