#include "PlayerChar.h"

void PlayerChar::setupCamera()
{
	camera.setPosAbsolute(getPos() + cameraLookAtVector * cameraDist);
	camera.setTargetAbsolute(getPos());

	camera.setProjectionAsOrtho
	(
		-cameraDist / 2,
		cameraDist / 2,
		-cameraDist / 2,
		cameraDist / 2,
		0.1,
		cameraDist * 2
	);

	//camera.setProjectionAsPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1, cameraDist * 2);
}

PlayerChar::PlayerChar(std::string const& playerCharPath, std::string const& lanternPath, float cameraDist, glm::vec3 cameraLookAtVector)
	: Model(playerCharPath)
{
	lantern = new Lantern(lanternPath);
	this->cameraDist = cameraDist;
	this->cameraLookAtVector = cameraLookAtVector;

	setupCamera();
}

void PlayerChar::Draw(Shader& shader)
{
	camera.setActiveCamera(shader);
	lantern->Draw(shader);
	Model::Draw(shader);
}

void PlayerChar::setPosAbsolute(glm::vec3 newPos)
{
	Model::setPosAbsolute(newPos);
	setupCamera();
}

void PlayerChar::translateBy(glm::vec3 vector)
{
	Model::translateBy(vector);
	setupCamera();
}

void PlayerChar::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		glm::vec3 front = getFrontVector();
		translateBy(front);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		glm::vec3 back = -getFrontVector();
		translateBy(back);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		glm::vec3 right = getRightVector();
		translateBy(right);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		glm::vec3 left = -getRightVector();
		translateBy(left);
	}
}
