#include "Camera.h"

void Camera::setActiveCamera(Shader& shader)
{
	glm::mat4 view = getCurrentViewMatrix();
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
	projType = ProjectionType::Ortho;
	orthoWidth = -left + right;
	orthoHeight = -bottom + top;
}

void Camera::setProjectionAsPerspective(float FOV, float aspectRatio, float minRange, float maxRange)
{
	projection = glm::perspective(FOV, aspectRatio, minRange, maxRange);
	projType = ProjectionType::Perspective;
}

std::vector<glm::vec3> Camera::getMouseCast(GLFWwindow* window, float width, float height)
{
	std::vector<glm::vec3> result = std::vector<glm::vec3>(2, glm::vec3(0.0f, 0.0f, 0.0f));;
	double d_cursor_x = 0;
	double d_cursor_y = 0;
	glfwGetCursorPos(window, &d_cursor_x, &d_cursor_y);

	float cursor_x = (float)d_cursor_x;
	float cursor_y = (float)d_cursor_y;

	if (projType == ProjectionType::Perspective)
	{
		//formula extrated from: https://stackoverflow.com/a/30005258
		cursor_x = cursor_x / (width * 0.5f) - 1.0f;
		cursor_y = cursor_y / (height * 0.5f) - 1.0f;

		glm::mat4 invVP = glm::inverse(projection * getCurrentViewMatrix());

		glm::vec4 screenPos = glm::vec4(cursor_x, -cursor_y, 1.0f, 1.0f);
		glm::vec4 worldPos = invVP * screenPos;
		result[0] = glm::normalize(glm::vec3(worldPos));
		result[1] = cameraPos;
	}
	else if (projType == ProjectionType::Ortho)
	{
		//formula modified from https://stackoverflow.com/a/66813405
		cursor_x = cursor_x * (orthoWidth / width) - (orthoWidth / 2);
		cursor_y = -(cursor_y * (orthoHeight / height) - (orthoHeight / 2));
		cursor_x = glm::clamp(cursor_x, -orthoWidth / 2, orthoWidth / 2);
		cursor_y = glm::clamp(cursor_y, -orthoHeight / 2, orthoHeight / 2);

		//std::cout << "mouse coords" << cursor_x << " " << cursor_y << "\n";
		//cursor_x = (2.0f * cursor_x / width - 1) * (orthoWidth / 2);
		//cursor_y = -(2.0f * cursor_y / height - 1) * (orthoHeight / 2);

		glm::vec3 camDirection = glm::normalize(cameraTarget - cameraPos);
		glm::vec3 cameraRight = glm::normalize(glm::cross(camDirection, cameraUp));
		glm::vec3 cameraUp_ = glm::normalize(glm::cross(cameraRight, camDirection));

		glm::vec3 rayOrigin = cameraPos + cameraRight * cursor_x + cameraUp_ * cursor_y;
		glm::vec3 rayDirection = glm::normalize(camDirection);

		result[0] = rayDirection;
		result[1] = rayOrigin;
	}
	return result;
}

glm::mat4 Camera::getCurrentViewMatrix()
{
	return glm::lookAt
	(
		cameraPos,
		cameraTarget,
		cameraUp
	);
}


