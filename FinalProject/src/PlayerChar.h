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

	Camera camera;
	float cameraDist;
	glm::vec3 cameraLookAtVector;

	void setupCamera();

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

	void processInput(GLFWwindow* window);
};

#endif