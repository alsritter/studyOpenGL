#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Material
{
public:
	Material( glm::vec3 _diffuse , glm::vec3 _specular ,float _shininess, float _metallic , float _Gloss);
	/*漫反射*/
	glm::vec3 diffuse ;
	/*镜面反射*/
	glm::vec3 specular ;
	/*反射度*/
	float gloss = 20;
	/*金属度*/
	float metallic = 0.1f;
	/*平滑度*/
	float Smoothness = 0.1f;


	~Material();

};

