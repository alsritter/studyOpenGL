#include "Camera.h"



Camera::Camera(glm::vec3 CameraPos, glm::vec3 CameraFront, glm::vec3 WorldUp)
	:WorldUp(WorldUp), CameraPos(CameraPos), CameraFront(CameraFront)
{
	CameraDirection = glm::normalize(CameraFront - CameraPos);
	CameraRight = glm::normalize(glm::cross(WorldUp, CameraDirection));
	CameraUp = glm::normalize(glm::cross(CameraDirection, CameraRight));
}

Camera::Camera(glm::vec3 CameraPos, float pitch, float yaw, glm::vec3 WorldUp) 
	:WorldUp(WorldUp), CameraPos(CameraPos) ,CameraFront(glm::vec3(0.0f, 0.0f, -1.0f)) ,Pitch(pitch) ,Yaw(yaw)
{
	/* CameraDirection 代表摄像机的前轴*/
	CameraDirection.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	CameraDirection.y = sin(glm::radians(Pitch));					
	CameraDirection.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	CameraRight = glm::normalize(glm::cross(WorldUp, CameraDirection));
	CameraUp = glm::normalize(glm::cross(CameraDirection, CameraRight));
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(CameraPos, CameraPos+CameraDirection , WorldUp);
}

glm::mat4 Camera::GetPerspective() {
	return glm::perspective(glm::radians(Fov), (WindowWidth / WindowHight), fovNear, fovFar);
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	CameraDirection = glm::normalize(front);
	CameraRight = glm::normalize(glm::cross(CameraDirection, WorldUp));
	CameraUp = glm::normalize(glm::cross(CameraRight, CameraDirection));
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {

	Yaw += xoffset * SenseX;
	Pitch += yoffset * SenseY;
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
	Fov += yoffset;
	if (Fov >= 170)
		Fov = 170;
	if (Fov <= 10)
		Fov = 10;
}

Camera::~Camera()
{
}
