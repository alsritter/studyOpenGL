#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

class Light
{
public:
	Light(glm::vec3 _Light_dir, glm::vec3 _LightColor, float _lightStrength);
	Light(glm::vec3 _Light_dir, glm::vec3 _LightColor, float _lightStrength, Shader* shader);
	void Draw_Light(glm::mat4 light_view, glm::mat4 light_projection);

	const char* type;//灯光类型
	glm::vec3 Light_Pos ;//点光专用
	glm::vec3 Light_dir ;//平行光专用
	glm::vec3 LightColor ;
	glm::vec3 SpecularColor = glm::vec3(1.0f, 1.0f, 1.0f);
	Shader* shader;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	float lightStrength = 0.2f;//光照强度
	~Light();



private:

	unsigned int VBO;
	unsigned int lightVAO;

	const float vertices[108] = {
	-0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 

	-0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f, 

	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 

	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 

	-0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f, -0.5f, 

	-0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f 
	};


};

