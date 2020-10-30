/*
*��Ŀ���ƣ�OpenGLlearn
*����ʱ�䣺2019.8.18
*�����ˣ�alsritter
*
*�޸�ʱ�䣺2019.8.18
*�޸����ݣ����������
*�޸��ˣ�alsritter
*�汾��1.0.0
*
*�޸�ʱ�䣺2019.9.14
*�޸����ݣ������ɫ����render����
*�޸��ˣ�alsritter
*�汾��1.1.0
*
*�޸�ʱ�䣺2019.9.15
*�޸����ݣ����Ե���ͼƬ
*�޸��ˣ�alsritter
*�汾��1.1.8
*
*�޸�ʱ�䣺2019.9.29
*�޸����ݣ�����������࣬�Լ��������
*�޸��ˣ�alsritter
*�汾��1.2
*
*�޸�ʱ�䣺2019.10.6
*�޸����ݣ���һЩ������װ�ɷ���
*�޸��ˣ�alsritter
*�汾��1.2.1
*
*
**/



#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/* ���type_ptr.hpp������ת����openGL�ܶ�ȡ��������ʽ */
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
#include<cmath>
#include"Shader.h"
#include"camera.h"
#include"stb_image.h"

using namespace std;

#pragma region ModeData

const float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};


unsigned int indices[] = {//�������˳��
	0,1,3,
	1,2,3
};


#pragma endregion

#pragma region ȫ�ֱ���

/*ȫ�ֱ�����*/
Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), 0.0f, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

float lastX;
float lastY;
bool firstMouse = false;

#pragma endregion

#pragma region ����ԭ��

/*����ԭ����*/
void checkInput(GLFWwindow* window, Camera* camera);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int Load_2D_Texture_To_Gpu(const char* TextureName, int TextureSlot, GLint level, GLint internalFormat, GLint Format);


#pragma endregion


int _main() {

#pragma region OpenGL��Window��ʼ��
	glfwInit();//�����ʼ��������д������������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		cout << "opengl window failed" << endl;
		glfwTerminate();
		system("PAUSE");
		return -1;
	}

	/*��������ڵ�����Ҫ������*/
	glfwMakeContextCurrent(window);
	/**/
	glewExperimental = true;

	/*��ʼ��ʧ�ܣ������ʼ������������Ĳ���ͬ������*/
	/*����������Ǹ������Լ��Կ�����չ�ļ���ͬʱҲ��ʶ�𱾵�ƽ̨��֧�ֵ�����openGL�߼���չ����*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLFW open failed" << std::endl;
		glfwTerminate();
		system("PAUSE");
		return -1;
	}
	glViewport(0, 0, 800, 600);
	Shader *shader = new Shader("Shader/vShader.vert", "Shader/fShader.frag");

#pragma endregion

#pragma region ���ֿ���

	/*������Ȳ���*/
	glEnable(GL_DEPTH_TEST);
	/*�ڵ����������֮������������ôȥ�ƶ���꣬��궼������ʾ�ˣ���Ҳ�����뿪���ڡ�*/
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	/*����������ģʽ������ʱѡ����������ģʽ*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

#pragma endregion

#pragma region ��ȡ����ķ���

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

#pragma endregion

#pragma region ��������

	/*����*/
	unsigned int Texture1 = Load_2D_Texture_To_Gpu("texture/container.jpg", 0, 0, GL_RGB, GL_RGB);
	unsigned int Texture2 = Load_2D_Texture_To_Gpu("texture/awesomeface.png", 1, 0, GL_RGBA, GL_RGBA);
	
	shader->Use();
	glUniform1i(glGetUniformLocation(shader->ID, "Texture1"),0);
	glUniform1i(glGetUniformLocation(shader->ID, "Texture2"), 1);

#pragma endregion

#pragma region Model_View_Projection_Space

/*���ò���*/
	cout << camera->CameraDirection.x << ' ' << camera->CameraDirection.y << ' ' << camera->CameraDirection.z << endl;
	cout << cos(glm::radians(0.0f)) << endl;
	unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
	glm::mat4 model;
	glm::mat4 view;
	view = camera->GetViewMatrix();
	glm::mat4 projection;
	projection = camera->GetPerspective();
	shader->SetMat4("model", model);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);

#pragma endregion
	
#pragma region ������

/*ѭ�����ƣ�ֱ���ر�*/
	while (!glfwWindowShouldClose(window))
	{
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		checkInput(window,camera);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(VAO);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		view = camera->GetViewMatrix();
		shader->SetMat4("view", view);
		projection = camera->GetPerspective();
		shader->SetMat4("projection", projection);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader->SetMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window); 
		/*����Ƿ���ʲô����*/
		glfwPollEvents();

	}

#pragma endregion

#pragma region �ͷ���Դ

/*�ͷŻ�ɾ����Դ*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete(camera);
	delete(shader);
	glfwTerminate();

#pragma endregion
	
	return 0;
}

#pragma region ����ʵ��

/*��ⰴ��*/
void checkInput(GLFWwindow* window ,Camera* camera) {

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS )
	{
		/*ע����������ô��ڹرգ�����Ӧ����true*/
		glfwSetWindowShouldClose(window, true);
	}
	//float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->CameraPos += cameraSpeed * camera->CameraDirection;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->CameraPos -= cameraSpeed * camera->CameraDirection;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->CameraPos -= glm::normalize(glm::cross(camera->CameraDirection, camera->CameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->CameraPos += glm::normalize(glm::cross(camera->CameraDirection, camera->CameraUp)) * cameraSpeed;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xpos - lastX;
	deltaY = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(deltaX, -deltaY);
	//cout << deltaX << ' ' << deltaY << endl;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//cout << xoffset << ' ' << yoffset << endl;
	camera->ProcessMouseScroll(yoffset);
}
unsigned int Load_2D_Texture_To_Gpu(const char* TextureName ,int TextureSlot ,GLint level ,GLint internalFormat ,GLint Format) {
	unsigned int texture;
	glGenTextures(1, &texture);
	/* ָ�������ĸ��� */
	glActiveTexture(GL_TEXTURE0 + TextureSlot);
	glBindTexture(GL_TEXTURE_2D, texture);
	/*openGL ��ͼƬ�������Ƿ�ת��*/
	stbi_set_flip_vertically_on_load(true);
	int width, hight, nrChannels;
	unsigned char* data = stbi_load(TextureName, &width, &hight, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, hight, 0, Format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		/*����ͼ����Դ��Ҫ�ͷ�*/
		stbi_image_free(data);

		return texture;
	}
	else
	{
		cout << "load texture fail!" << endl;
		system("PAUSE");

		/*����ͼ����Դ��Ҫ�ͷ�*/
		stbi_image_free(data);
		return NULL;
	}

}

#pragma endregion

