#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	/* 函数 */
	Camera(glm::vec3 CameraPos, glm::vec3 CameraTarget,  glm::vec3 WorldUp);
	Camera(glm::vec3 CameraPos, float pitch, float yaw, glm::vec3 WorldUp);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetPerspective();
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);

	/* 变量 */
	glm::vec3 CameraPos;
	glm::vec3 WorldUp;
	glm::vec3 CameraFront;
	glm::vec3 CameraRight;
	glm::vec3 CameraUp;
	glm::vec3 CameraDirection;
	float Pitch;
	float Yaw;
	/* 用于设置鼠标灵敏度 */
	float SenseX = 0.1f;
	float SenseY = 0.1f;
	/* 相机绘制距离 与 角度 */
	float fovNear = 0.1f;
	float fovFar = 100.0f;
	float Fov = 45.0f;
	/* 窗口宽高 */
	float WindowHight = 600;
	float WindowWidth = 800;
	~Camera();

private:
	void updateCameraVectors();
};

