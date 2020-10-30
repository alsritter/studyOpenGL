#include "Light.h"



Light::Light(glm::vec3 _Light_dir, glm::vec3 _LightColor, float _lightStrength)
	:Light_dir(_Light_dir),LightColor(_LightColor), lightStrength(_lightStrength),type("DirLight"){}


Light::Light(glm::vec3 _Light_Pos, glm::vec3 _LightColor, float _lightStrength, Shader* shader)
	: Light_Pos(_Light_Pos), LightColor(_LightColor), lightStrength(_lightStrength), shader(shader), type("PointLight") {}

void Light::Draw_Light(glm::mat4 light_view , glm::mat4 light_projection)
{
	if (type == "PointLight")
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		/* 为灯光新建个vao */
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);//bind到新vao来
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		shader->Use();
		glm::mat4 light_model;
		light_model = glm::translate(light_model, Light_Pos);
		light_model = glm::scale(light_model, glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetMat4("view", light_view);
		shader->SetMat4("projection", light_projection);
		shader->SetMat4("model", light_model);
		shader->SetVec3("lightColor", LightColor);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);//解绑

	}
}



Light::~Light()
{
	delete(shader);
}
