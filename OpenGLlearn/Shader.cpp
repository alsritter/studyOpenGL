#include "Shader.h"



Shader::Shader(const GLchar *VertexPath, const GLchar *FragmentPath)
{
	std::string VertexCode;
	std::string FragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit || std::ifstream::failbit);//根据设置的状态来throw异常
	fShaderFile.exceptions(std::ifstream::badbit || std::ifstream::failbit);
	try
	{
		//打开文件
		vShaderFile.open(VertexPath);
		fShaderFile.open(FragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		//读取文件
		vShaderStream << vShaderFile.rdbuf();//实际这个string流就是个中转站(因为早期只有char*，所以需要先转成string流)
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件
		vShaderFile.close();
		fShaderFile.close();

		VertexCode = vShaderStream.str();
		FragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "shaderFile io error" << std::endl;
	}
	const char* vShaderCode = VertexCode.c_str();//编译只能编译char*类型
	const char* fShaderCode = FragmentCode.c_str();

	//编译着色器代码
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/*shader来源函数 第二参数指定了传递的源码字符串数量*/
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);	/*编译shader*/
	/*用于检验是否编译成功*/
	int success;
	char infoLog[512];
	success = NULL;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		system("PAUSE");
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/*片段着色器*/
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	success = NULL;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		system("PAUSE");
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/*shaderProgram：创建一个shader程序，把顶点片段连接起来*/
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);//别漏了这个把它们连起来的语句
	success = NULL;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use() {
	glUseProgram(ID);
}

void Shader::SetBool(const std::string &name, bool value) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::SetFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::SetInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::SetFloat2(const std::string &name, float value, float value2) const {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value ,value2);
}
void Shader::SetVec3(const std::string &name, float value, float value2, float value3) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value, value2 ,value3);
}
void Shader::SetFloat4(const std::string &name, float value, float value2, float value3, float value4) const {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value, value2, value3, value4);
}

void Shader::SetMat4(const std::string &name, glm::mat4 mat4) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::SetVec3(const std::string &name, glm::vec3 vec3) {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec3));
}

void Shader::SetVec3(const std::string &name, ImVec4 imVec4) {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(glm::vec3(imVec4.x, imVec4.y, imVec4.z)));
}


Shader::~Shader()
{
}
