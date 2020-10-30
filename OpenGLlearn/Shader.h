#pragma once
#include<GL/glew.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


class Shader
{
public:
	unsigned int ID;
	Shader(const GLchar *VertexPath,const GLchar *FragmentPath);//Path:路径
	void Use();
	//函数接const表示该函数不能修改成员变量的值
	void SetFloat(const std::string &name, float value) const;
	void SetFloat2(const std::string &name, float value, float value2) const;
	void SetFloat4(const std::string &name, float value, float value2, float value3, float value4) const;

	void SetMat4(const std::string &name, glm::mat4 mat4);
	void SetVec3(const std::string &name, glm::vec3 vec3);
	void SetVec3(const std::string &name, ImVec4 imVec4);
	void SetVec3(const std::string &name, float value, float value2, float value3) const;

	void SetInt(const std::string &name, int value) const;
	void SetBool(const std::string &name, bool value) const;


	~Shader();
};

