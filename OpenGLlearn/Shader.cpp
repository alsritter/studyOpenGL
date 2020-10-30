#include "Shader.h"



Shader::Shader(const GLchar *VertexPath, const GLchar *FragmentPath)
{
	std::string VertexCode;
	std::string FragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit || std::ifstream::failbit);//�������õ�״̬��throw�쳣
	fShaderFile.exceptions(std::ifstream::badbit || std::ifstream::failbit);
	try
	{
		//���ļ�
		vShaderFile.open(VertexPath);
		fShaderFile.open(FragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		//��ȡ�ļ�
		vShaderStream << vShaderFile.rdbuf();//ʵ�����string�����Ǹ���תվ(��Ϊ����ֻ��char*��������Ҫ��ת��string��)
		fShaderStream << fShaderFile.rdbuf();
		//�ر��ļ�
		vShaderFile.close();
		fShaderFile.close();

		VertexCode = vShaderStream.str();
		FragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "shaderFile io error" << std::endl;
	}
	const char* vShaderCode = VertexCode.c_str();//����ֻ�ܱ���char*����
	const char* fShaderCode = FragmentCode.c_str();

	//������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/*shader��Դ���� �ڶ�����ָ���˴��ݵ�Դ���ַ�������*/
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);	/*����shader*/
	/*���ڼ����Ƿ����ɹ�*/
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
	/*Ƭ����ɫ��*/
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
	/*shaderProgram������һ��shader���򣬰Ѷ���Ƭ����������*/
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);//��©����������������������
	success = NULL;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
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
