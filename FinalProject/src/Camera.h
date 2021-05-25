#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"

namespace ProjectionType
{
	enum Types {
		Ortho,
		Perspective
	};
};

class Camera
{
private:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f);
	ProjectionType::Types projType;

	float orthoWidth;
	float orthoHeight;

public: 
	void setActiveCamera(Shader& shader);

	void setPosAbsolute(glm::vec3 newPos);

	void translateBy(glm::vec3 vector);

	void setTargetAbsolute(glm::vec3 newTarget);

	void setCameraUp(glm::vec3 newCameraUp);

	void setProjectionAsOrtho(float left, float right, float bottom, float top, float minRange, float maxRange);

	void setProjectionAsPerspective(float FOV, float aspectRatio, float minRange, float maxRange);

	//result[0] == cast direction, result[1] == cast origin
	std::vector<glm::vec3> getMouseCast(GLFWwindow* window, float width, float height);

	glm::mat4 getCurrentViewMatrix();
};

#endif
