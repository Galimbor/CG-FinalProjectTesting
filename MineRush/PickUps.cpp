#include "PickUps.h"
#include "MovingBody.h"

PickUps::PickUps(std::string const& modelPath)
	: Model(modelPath)
{
	rotSpeed = 2.0f;
}

void PickUps::Draw(Shader& shader, float deltaTime)
{
	glm::vec3 yAxis = glm::vec3(0.0f, 0.1f, 0.0f);
	rotateBySpeed(glm::radians(90.0f), yAxis, deltaTime);
	MovingBody::Draw(shader, deltaTime);
}
