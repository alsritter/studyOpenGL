/*
*项目名称：OpenGLlearn
*创建时间：2019.8.18
*创建人：alsritter
*
*修改时间：2019.8.18
*修改内容：完成主体框架
*修改人：alsritter
*版本：1.0.0
*
*修改时间：2019.9.14
*修改内容：添加着色器（render）类
*修改人：alsritter
*版本：1.1.0
*
*修改时间：2019.9.15
*修改内容：尝试导入图片
*修改人：alsritter
*版本：1.1.8
*
*修改时间：2019.9.29
*修改内容：构建摄像机类，以及整理代码
*修改人：alsritter
*版本：1.2
*
*修改时间：2019.10.6
*修改内容：把一些操作封装成方法
*修改人：alsritter
*版本：1.2.1
*
*
**/



#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/* 这个type_ptr.hpp是用来转化成openGL能读取的向量形式 */
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


unsigned int indices[] = {//顶点绘制顺序
	0,1,3,
	1,2,3
};


#pragma endregion

#pragma region 全局变量

/*全局变量区*/
Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), 0.0f, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

float lastX;
float lastY;
bool firstMouse = false;

#pragma endregion

#pragma region 函数原型

/*函数原型区*/
void checkInput(GLFWwindow* window, Camera* camera);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int Load_2D_Texture_To_Gpu(const char* TextureName, int TextureSlot, GLint level, GLint internalFormat, GLint Format);


#pragma endregion


int _main() {

#pragma region OpenGL和Window初始化
	glfwInit();//这个初始化函数别写错！！！！！！
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

	/*把这个窗口当成主要上下文*/
	glfwMakeContextCurrent(window);
	/**/
	glewExperimental = true;

	/*初始化失败，这个初始化函数与上面的不是同个东西*/
	/*这个函数是那个适配自己显卡的拓展文件，同时也能识别本地平台所支持的所有openGL高级拓展函数*/
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

#pragma region 各种开关

	/*开启深度测试*/
	glEnable(GL_DEPTH_TEST);
	/*在调用这个函数之后，无论我们怎么去移动鼠标，光标都不会显示了，它也不会离开窗口。*/
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	/*设置纹理环绕模式和缩放时选择的纹理过滤模式*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

#pragma endregion

#pragma region 读取数组的方法

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

#pragma region 导入纹理

	/*纹理*/
	unsigned int Texture1 = Load_2D_Texture_To_Gpu("texture/container.jpg", 0, 0, GL_RGB, GL_RGB);
	unsigned int Texture2 = Load_2D_Texture_To_Gpu("texture/awesomeface.png", 1, 0, GL_RGBA, GL_RGBA);
	
	shader->Use();
	glUniform1i(glGetUniformLocation(shader->ID, "Texture1"),0);
	glUniform1i(glGetUniformLocation(shader->ID, "Texture2"), 1);

#pragma endregion

#pragma region Model_View_Projection_Space

/*设置参数*/
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
	
#pragma region 绘制区

/*循环绘制，直到关闭*/
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
		/*检测是否按了什么按键*/
		glfwPollEvents();

	}

#pragma endregion

#pragma region 释放资源

/*释放或删除资源*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete(camera);
	delete(shader);
	glfwTerminate();

#pragma endregion
	
	return 0;
}

#pragma region 函数实现

/*检测按键*/
void checkInput(GLFWwindow* window ,Camera* camera) {

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS )
	{
		/*注意这个是设置窗口关闭，所以应该是true*/
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
	/* 指定纹理丢哪个槽 */
	glActiveTexture(GL_TEXTURE0 + TextureSlot);
	glBindTexture(GL_TEXTURE_2D, texture);
	/*openGL 与图片的坐标是翻转的*/
	stbi_set_flip_vertically_on_load(true);
	int width, hight, nrChannels;
	unsigned char* data = stbi_load(TextureName, &width, &hight, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, hight, 0, Format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		/*用完图像资源后要释放*/
		stbi_image_free(data);

		return texture;
	}
	else
	{
		cout << "load texture fail!" << endl;
		system("PAUSE");

		/*用完图像资源后要释放*/
		stbi_image_free(data);
		return NULL;
	}

}

#pragma endregion

