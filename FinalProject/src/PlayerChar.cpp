#include "PlayerChar.h"

void PlayerChar::setupCamera()
{
	camera.setPosAbsolute(getPos() - cameraLookAtVector * cameraDist);
	camera.setTargetAbsolute(getPos());
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
}
