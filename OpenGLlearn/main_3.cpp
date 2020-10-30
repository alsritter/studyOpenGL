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
*修改时间：2019.10.7
*修改内容：增加光照系统，添加上了GUI
*修改人：alsritter
*版本：1.3.0
*
*
*修改时间：2019.10.8
*修改内容：完善灯光系统，区分出了点光源和平行光
*修改人：alsritter
*版本：1.3.5
*
*
**/



#define GLEW_STATIC
#define GLFW_EXPOSE_NATIVE_GLX

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/* 这个type_ptr.hpp是用来转化成openGL能读取的向量形式 */
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

#include "Shader.h"
#include "camera.h"
#include "Material.h"
#include "Light.h"


#include "Mesh2.h"
#include "Model2.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"




using namespace std;

#pragma region ModeData

const float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f
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

//灯的位置
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
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
bool cursorDisplay = false;
bool SuspendPollEvents = false;

bool materialWindow = false;
bool mainLightWindow = false;
bool DirLightWindow = false;
#define NR_POINT_LIGHTS 4 
bool pointLightWindow[NR_POINT_LIGHTS];



//Light Dirlight(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(1.0f, 0.86f, 0.73f), glm::vec3(1.0f, 1.0f, 1.0f), 0.23);
//
//glm::vec3 PointLightColor = glm::vec3(1.0f, 0.86f, 0.73f);
//float PointlightStrength = 0.2;
//Light Pointlight_1(pointLightPositions[0], PointLightColor, glm::vec3(1.0f, 1.0f, 1.0f), 0.23);
//Light Pointlight_2(pointLightPositions[1], PointLightColor, glm::vec3(1.0f, 1.0f, 1.0f), 0.23);
//Light Pointlight_3(pointLightPositions[2], PointLightColor, glm::vec3(1.0f, 1.0f, 1.0f), 0.23);
//Light Pointlight_4(pointLightPositions[3], PointLightColor, glm::vec3(1.0f, 1.0f, 1.0f), 0.23);

Material material_1( glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),20,0.1f,0.1f);


#pragma endregion

#pragma region 函数原型

/*函数原型区*/
void checkInput(GLFWwindow* window, Camera* camera);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int Load_2D_Texture_To_Gpu(const char* TextureName, int TextureSlot, GLint level, GLint internalFormat, GLint Format);
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void PointLightWindowContent(Light * Pointlight);

#pragma endregion


int main(int argc, char* argv[]) {

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
	//Shader *shader = new Shader("Shader/vShader_normals.vert", "Shader/fShader_normals.frag");
	//Shader *lightShader = new Shader("Shader/LightShader.vert", "Shader/LightShader.frag");

	//创建并绑定ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");
	

#pragma endregion

#pragma region 各种开关

	/*开启深度测试*/
	glEnable(GL_DEPTH_TEST);
	/*在调用这个函数之后，无论我们怎么去移动鼠标，光标都不会显示了，它也不会离开窗口。*/
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	///*设置纹理环绕模式和缩放时选择的纹理过滤模式*/
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

#pragma endregion

#pragma region 读取数组的方法

	/*unsigned int VAO;
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);*/

	///* 为灯光新建个vao */
	//unsigned int lightVAO;
	//glGenVertexArrays(1, &lightVAO);
	//glBindVertexArray(lightVAO);//bind到新vao来
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

#pragma endregion

#pragma region 导入纹理

	/*纹理*/
	//glBindVertexArray(VAO);
	//unsigned int Texture1 = Load_2D_Texture_To_Gpu("texture/container2.png", 0, 0, GL_RGBA, GL_RGBA);
	//unsigned int Texture2 = Load_2D_Texture_To_Gpu("texture/container2_specular.png", 1, 0, GL_RGBA, GL_RGBA);
	//shader->Use();
	//shader->SetInt("material.diffuse", 0);
	//shader->SetInt("material.specular", 1);

#pragma endregion

#pragma region Model_View_Projection_Space

/*设置参数*/

	//cout << camera->CameraDirection.x << ' ' << camera->CameraDirection.y << ' ' << camera->CameraDirection.z << endl;
	//cout << cos(glm::radians(0.0f)) << endl;
	//unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
	glm::mat4 view;
	view = camera->GetViewMatrix();
	glm::mat4 projection;
	projection = camera->GetPerspective();
	//shader->SetMat4("view", view);
	//shader->SetMat4("projection", projection);

#pragma endregion
	
	string exePath = argv[0];
	Model2 model(exePath.substr(0,exePath.find_last_of('\\'))+"\\Model\\"+"nanosuit.obj");
	Shader modelshader("Shader/vShader_normals.vert", "Shader/fShader_normals.frag");

	Light* DirLight = new Light(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.23);
	Light* PointLight_1 = new Light(glm::vec3(0.7f, 0.2f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.23, new Shader("Shader/LightShader.vert", "Shader/LightShader_1.frag"));
	Light* PointLight_2 = new Light(glm::vec3(2.3f, -3.3f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.23, new Shader("Shader/LightShader.vert", "Shader/LightShader_2.frag"));
	Light* PointLight_3 = new Light(glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.23, new Shader("Shader/LightShader.vert", "Shader/LightShader_3.frag"));
	Light* PointLight_4 = new Light(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.23, new Shader("Shader/LightShader.vert", "Shader/LightShader_4.frag"));

	

#pragma region 绘制区

/*循环绘制，直到关闭*/
	while (!glfwWindowShouldClose(window))
	{

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//改变窗口大小时调用

		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//启动imgui框架
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//2. 展示一个我们自己创建的简单窗口。我们使用开始/结束对创建命名窗口。
		{
			//ImGui::Begin("Light data");                          // 窗口标题

			//ImGui::Text("This is Light data."); 
			//ImGui::ColorEdit3("DirlightColor", (float*)&Dirlight.LightColor);
			//ImGui::ColorEdit3("PointlightColor", (float*)&PointLightColor);
			//ImGui::ColorEdit3("DirlightAmbientColor", (float*)&Dirlight.AmbientColor);
			//ImGui::ColorEdit3("DirlightSpecularColor", (float*)&Dirlight.SpecularColor);
			//ImGui::SliderFloat("DirlightStrength", &Dirlight.lightStrength, 0.01f, 0.5f);
			//ImGui::SliderFloat("PointlightStrength", &PointlightStrength, 0.01f, 2.0f);
			//ImGui::Text("");
			//ImGui::Text("This is Material panel.");
			////ImGui::ColorEdit3("MaterialDiffuse", (float*)&material_1.diffuse);
			////ImGui::ColorEdit3("MaterialSpecular", (float*)&material_1.specular);
			//ImGui::SliderFloat("MaterialGloss", &material_1.gloss, 8.0f, 256.0f);
			//ImGui::SliderFloat("MaterialSmoothness", &material_1.Smoothness, 0.01f, 1.0f);
			//ImGui::SliderFloat("Materialmetallic", &material_1.metallic, 0.01f, 1.0f);
			////ImGui::SameLine();
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//ImGui::End();
		}

		ImGui::Begin("MainData Window");
		ImGui::Checkbox("Material Window", &materialWindow);
		ImGui::Checkbox("Light Window", &mainLightWindow);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		if (materialWindow)
		{
			ImGui::Begin("Material Window");
			ImGui::Text("MaterialWindow");
			ImGui::End();
		}

		if (mainLightWindow)
		{
			ImGui::Begin("Light Window");
			ImGui::Text("main Light Window");
			ImGui::Checkbox("Dir Light Window", &DirLightWindow);
#pragma region 点光源面板开关
#if NR_POINT_LIGHTS == 1
			ImGui::Checkbox("Point Light Window", &pointLightWindow[0]);
#elif NR_POINT_LIGHTS == 2
			ImGui::Checkbox("Point Light Window 1", &pointLightWindow[0]);
			ImGui::Checkbox("Point Light Window 2", &pointLightWindow[1]);
#elif NR_POINT_LIGHTS == 3
			ImGui::Checkbox("Point Light Window 1", &pointLightWindow[0]);
			ImGui::Checkbox("Point Light Window 2", &pointLightWindow[1]);
			ImGui::Checkbox("Point Light Window 3", &pointLightWindow[2]);
#elif NR_POINT_LIGHTS == 4
			ImGui::Checkbox("Point Light Window 1", &pointLightWindow[0]);
			ImGui::Checkbox("Point Light Window 2", &pointLightWindow[1]);
			ImGui::Checkbox("Point Light Window 3", &pointLightWindow[2]);
			ImGui::Checkbox("Point Light Window 4", &pointLightWindow[3]);
#else
			cout << "点光源数量错误" << endl;
			system("pause");
			return -1;
#endif
#pragma endregion

			ImGui::End();
		}

		if (DirLightWindow)
		{
			ImGui::Begin("DirLightWindow");
			ImGui::Text("DirLightWindow");
			//ImGui::SliderFloat("DirlightStrength", ! , 0.01f, 0.5f);
			//ImGui::ColorEdit3("DirlightColor", ! );
			ImGui::Text("Color widget:");
			//ImGui::SameLine(); //同一条线
			ImGui::End();
		}

#pragma region 点光源窗口

#if NR_POINT_LIGHTS == 1

		if (pointLightWindow[0])
		{
			ImGui::Begin("pointLightWindow 1");
			PointLightWindowContent(PointLight_1);
			ImGui::Text("pointLightWindow 1");
			ImGui::End();
		}

#elif NR_POINT_LIGHTS == 2

		if (pointLightWindow[0])
		{
			ImGui::Begin("pointLightWindow 1");
			PointLightWindowContent(PointLight_1);
			ImGui::Text("pointLightWindow 1");
			ImGui::End();
		}
		if (pointLightWindow[1])
		{
			ImGui::Begin("pointLightWindow 2");
			PointLightWindowContent(PointLight_2);
			ImGui::Text("pointLightWindow 2");
			ImGui::End();
		}


#elif NR_POINT_LIGHTS == 3

		if (pointLightWindow[0])
		{
			ImGui::Begin("pointLightWindow 1");
			PointLightWindowContent(PointLight_1);
			ImGui::Text("pointLightWindow 1");
			ImGui::End();
		}
		if (pointLightWindow[1])
		{
			ImGui::Begin("pointLightWindow 2");
			PointLightWindowContent(PointLight_2);
			ImGui::Text("pointLightWindow 2");
			ImGui::End();
		}
		if (pointLightWindow[2])
		{
			ImGui::Begin("pointLightWindow 3");
			PointLightWindowContent(PointLight_3);
			ImGui::Text("pointLightWindow 3");
			ImGui::End();
		}

#elif NR_POINT_LIGHTS == 4

		if (pointLightWindow[0])
		{
			ImGui::Begin("pointLightWindow 1");
			PointLightWindowContent(PointLight_1);
			ImGui::Text("pointLightWindow 1");
			ImGui::End();
		}
		if (pointLightWindow[1])
		{
			ImGui::Begin("pointLightWindow 2");
			PointLightWindowContent(PointLight_2);
			ImGui::Text("pointLightWindow 2");
			ImGui::End();
		}
		if (pointLightWindow[2])
		{
			ImGui::Begin("pointLightWindow 3");
			PointLightWindowContent(PointLight_3);
			ImGui::Text("pointLightWindow 3");
			ImGui::End();
		}
		if (pointLightWindow[3])
		{
			ImGui::Begin("pointLightWindow 4");
			PointLightWindowContent(PointLight_4);
			ImGui::Text("pointLightWindow 4");
			ImGui::End();
		}
#else 

		cout << "点光源数量错误" << endl;
		system("pause");
		return -1;

#endif 

#pragma endregion




		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		checkInput(window,camera);

		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		if (!SuspendPollEvents)
		{
			view = camera->GetViewMatrix();
			//cout << camera->CameraFront.x << endl;
			projection = camera->GetPerspective();
		}

		PointLight_1->Draw_Light(view, projection);
		PointLight_2->Draw_Light(view, projection);
		PointLight_3->Draw_Light(view, projection);
		PointLight_4->Draw_Light(view, projection);

		model.Draw(modelshader);

		/*glBindVertexArray(lightVAO);
		lightShader->Use();
		lightShader->SetVec3("objectColor", PointLightColor);
		lightShader->SetVec3("lightColor", Dirlight.LightColor);
		lightShader->SetMat4("view", view);
		lightShader->SetMat4("projection", projection);

		for (unsigned int i = 0; i < 4; i++)
		{
			glm::mat4 light_model;
			light_model = glm::translate(light_model, pointLightPositions[i]);
			light_model = glm::scale(light_model, glm::vec3(0.2f, 0.2f, 0.2f));
			lightShader->SetMat4("model", light_model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/


		//glBindVertexArray(VAO);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//shader->Use();
		//shader->SetMat4("view", view);
		//shader->SetVec3("viewPos", camera->CameraPos );
		//shader->SetMat4("projection", projection);

#pragma region 把灯光参数传进去

		/*shader->SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader->SetVec3("dirLight.ambient", Dirlight.AmbientColor);
		shader->SetVec3("dirLight.diffuse", Dirlight.LightColor);
		shader->SetVec3("dirLight.specular", Dirlight.SpecularColor);
		shader->SetFloat("dirLight.strength", Dirlight.lightStrength);

		shader->SetVec3("pointLights[0].position", pointLightPositions[0]);
		shader->SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVec3("pointLights[0].diffuse", PointLightColor);
		shader->SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		shader->SetFloat("pointLights[0].constant", 1.0f);
		shader->SetFloat("pointLights[0].linear", 0.09);
		shader->SetFloat("pointLights[0].quadratic", 0.032);
		shader->SetFloat("pointLights[0].strength", PointlightStrength);

		shader->SetVec3("pointLights[1].position", pointLightPositions[1]);
		shader->SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVec3("pointLights[1].diffuse", PointLightColor);
		shader->SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		shader->SetFloat("pointLights[1].constant", 1.0f);
		shader->SetFloat("pointLights[1].linear", 0.09);
		shader->SetFloat("pointLights[1].quadratic", 0.032);
		shader->SetFloat("pointLights[1].strength", PointlightStrength);

		shader->SetVec3("pointLights[2].position", pointLightPositions[2]);
		shader->SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVec3("pointLights[2].diffuse", PointLightColor);
		shader->SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		shader->SetFloat("pointLights[2].constant", 1.0f);
		shader->SetFloat("pointLights[2].linear", 0.09);
		shader->SetFloat("pointLights[2].quadratic", 0.032);
		shader->SetFloat("pointLights[2].strength", PointlightStrength);

		shader->SetVec3("pointLights[3].position", pointLightPositions[3]);
		shader->SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVec3("pointLights[3].diffuse", PointLightColor);
		shader->SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		shader->SetFloat("pointLights[3].constant", 1.0f);
		shader->SetFloat("pointLights[3].linear", 0.09);
		shader->SetFloat("pointLights[3].quadratic", 0.032);
		shader->SetFloat("pointLights[3].strength", PointlightStrength);*/

#pragma endregion

		

		/*shader->SetFloat("material.gloss", material_1.gloss);
		shader->SetFloat("material.Smoothness", material_1.Smoothness);
		shader->SetFloat("material.metallic", material_1.metallic); */

	
		//for (unsigned int i = 0; i < 10; i++)
		//{
		//	glm::mat4 _model;
		//	_model = glm::translate( _model, cubePositions[i]);
		//	//_model = glm::translate(_model, glm::vec3(0.0f,(float)i/0.5f,0.0f));
		//	float angle = 20.0f * i;
		//	_model = glm::rotate(_model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	shader->SetMat4("model", _model);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		{
			// Rendering 注意渲染这个imgui要放在最后
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			glfwSwapBuffers(window);
			/*检测是否按了什么按键*/
			glfwPollEvents();
			glfwSetKeyCallback(window, key_callback);
		}
	}

#pragma endregion

#pragma region 释放资源

/*释放或删除资源*/
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	delete(DirLight);
	delete(PointLight_1);
	delete(PointLight_2);
	delete(PointLight_3);
	delete(PointLight_4);
	delete(camera);
	//delete(shader);
	//delete(lightShader);

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

#pragma endregion
	
	return 0;
}

#pragma region 函数实现

/*检测按键（不随帧数改变检测速度）*/
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
		if (cursorDisplay)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			SuspendPollEvents = true;
			cursorDisplay = false;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			SuspendPollEvents = false;
			cursorDisplay = true;
		}
	}
}
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
/*检测鼠标的移动*/
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
/*鼠标滚轮*/
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//cout << xoffset << ' ' << yoffset << endl;
	camera->ProcessMouseScroll(yoffset);
}

//unsigned int Load_2D_Texture_To_Gpu(const char* TextureName ,int TextureSlot ,GLint level ,GLint internalFormat ,GLint Format) {
//	unsigned int texture;
//	glGenTextures(1, &texture);
//	/* 指定纹理丢哪个槽 */
//	glActiveTexture(GL_TEXTURE0 + TextureSlot);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	/*openGL 与图片的坐标是翻转的*/
//	stbi_set_flip_vertically_on_load(true);
//	int width, hight, nrChannels;
//	unsigned char* data = stbi_load(TextureName, &width, &hight, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, hight, 0, Format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		/*用完图像资源后要释放*/
//		stbi_image_free(data);
//
//		return texture;
//	}
//	else
//	{
//		cout << "load texture fail!" << endl;
//		system("PAUSE");
//
//		/*用完图像资源后要释放*/
//		stbi_image_free(data);
//		return NULL;
//	}
//
//}
/*实时更新窗口大小*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camera->WindowWidth = width;
	camera->WindowHight = height;
}
/*点光源窗口设置*/
void PointLightWindowContent(Light * Pointlight ) {
	float v[3] = { Pointlight->Light_Pos.x, Pointlight->Light_Pos.y, Pointlight->Light_Pos.z };
	ImGui::ColorEdit3("PointlightColor", (float*)&Pointlight->LightColor);
	//ImGui::DragFloat3("PointlightPos", v);
	ImGui::SliderFloat3("MaterialGloss", v, -1.0f, 1.0f);

	Pointlight->Light_Pos = glm::vec3(v[0], v[1], v[2]);

}

#pragma endregion

