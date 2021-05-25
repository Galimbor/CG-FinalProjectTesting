#include "Camera.h"

void Camera::setActiveCamera(Shader& shader)
{
	glm::mat4 view = glm::lookAt
	(
		cameraPos,
		cameraTarget,
		cameraUp
	);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
}

void Camera::setPosAbsolute(glm::vec3 newPos)
{
	this->cameraPos = newPos;
}

void Camera::translateBy(glm::vec3 vector)
{
	this->cameraPos += vector;
}

void Camera::setTargetAbsolute(glm::vec3 newTarget)
{
	this->cameraTarget = newTarget;
}

void Camera::setCameraUp(glm::vec3 newCameraUp)
{
	this->cameraPos = newCameraUp;
}

void Camera::setProjectionAsOrtho(float left, float right, float bottom, float top, float minRange, float maxRange)
{
	projection = glm::ortho(left, right, bottom, top, minRange, maxRange);
}

void Camera::setProjectionAsPerspective(float FOV, float aspectRatio, float minRange, float maxRange)
{
	projection = glm::perspective(FOV, aspectRatio, minRange, maxRange);
}


