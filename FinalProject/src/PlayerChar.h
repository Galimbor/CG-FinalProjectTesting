#ifndef PLAYERCHAR_CLASS_H
#define PLAYERCHAR_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Model.h"
#include "Camera.h"
#include "Lantern.h"

class PlayerChar : public Model
{
private:
	Lantern* lantern = nullptr;
	glm::vec3 lanternAnchorPoint;
	bool holdingLantern = true;

	Camera camera;
	float cameraDist;
	glm::vec3 cameraLookAtVector;

	void setupCamera();

	void setupLantern();

	glm::vec3 getLanternAnchorPoint();

public:
	PlayerChar
	(
		std::string const& playerCharPath,
		std::string const& lanternPath,
		float cameraDist,
		glm::vec3 cameraLookAtVector
	);

	virtual void Draw(Shader& shader) override;

	virtual void setPosAbsolute(glm::vec3 newPos) override;

	virtual void translateBy(glm::vec3 vector) override;

	virtual void setRotationAbsolute(float angle, glm::vec3 rotationAxis) override;

	virtual void rotateBy(float angle, glm::vec3 rotationAxis) override;

	void processInput(GLFWwindow* window, float deltaTime);

	void updateLookAt(GLFWwindow* window, float width, float height, float deltaTime);

	void throwLantern(float launchSpeed);
};

#endif