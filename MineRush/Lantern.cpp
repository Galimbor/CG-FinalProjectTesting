#include "Lantern.h"

Lantern::Lantern(std::string const& modelPath)
	: Model(modelPath)
{
}

void Lantern::Draw(Shader& shader)
{
	doProjectileMov();
	Model::Draw(shader);
}

void Lantern::makeProjectile(float launchSpeed)
{
	isProjectile = true;
	moveSpeed = launchSpeed;
	projectileStartTime = glfwGetTime();
	launchedPos = getPos();

	
	glm::vec2 frontPlanar = glm::vec2(getFrontVector().x, getFrontVector().z);
	glm::vec2 xAxis = glm::vec2(1.0f, 0.0f);
	float dotProduct = glm::dot(xAxis, frontPlanar);
	float xAxis_Magnitude = glm::length(xAxis);
	float frontPlanar_Magnitude = glm::length(frontPlanar);

	float angle = glm::acos(dotProduct / (xAxis_Magnitude * frontPlanar_Magnitude));

	speedComps[0] = glm::cos(angle) * moveSpeed;
	speedComps[1] = -glm::sin(angle) * moveSpeed;
}

void Lantern::doProjectileMov()
{
	if (isProjectile)
	{
		glm::vec3 newPos;
		float x_moveSpeed = speedComps[0];
		float z_moveSpeed = speedComps[1];
		newPos.x = MovingBody::computeTranslationEquation(launchedPos.x, x_moveSpeed, 0, glfwGetTime() - projectileStartTime)[0];
		newPos.y = MovingBody::computeTranslationEquation(launchedPos.y, 0, -9.8f, glfwGetTime() - projectileStartTime)[0];
		newPos.z = MovingBody::computeTranslationEquation(launchedPos.z, z_moveSpeed, 0, glfwGetTime() - projectileStartTime)[0];
		if (newPos.y < 0.0f)
		{
			newPos.y = 0.0f;
			isProjectile = false;
			isBouncing = true;
			bouncePos = newPos;
			bounceCount = 1;
			bounceSpeed = -MovingBody::computeTranslationEquation(launchedPos.y, 0, -9.8f, glfwGetTime() - projectileStartTime)[1];
			bounceStartTime = glfwGetTime();
		}
		setPosAbsolute(newPos);
		//std::cout << "newPos: " << newPos.x << " " << newPos.y << " " << newPos.z << "\n";
	}

	if (isBouncing)
	{
		doBounces();
		if (bounceCount > maxBounces)
		{
			isBouncing = false;
		}
	}
}

void Lantern::doBounces()
{
	glm::vec3 newPos;
	float x_moveSpeed = speedComps[0] + speedComps[0] * bounceSpeedMod * bounceCount;
	float y_moveSpeed = bounceSpeed / (bounceCount + 1);
	float z_moveSpeed = speedComps[1] + speedComps[1] * bounceSpeedMod * bounceCount;
	newPos.x = MovingBody::computeTranslationEquation(bouncePos.x, x_moveSpeed, 0, glfwGetTime() - bounceStartTime)[0];
	newPos.y = MovingBody::computeTranslationEquation(bouncePos.y, y_moveSpeed, -9.8f, glfwGetTime() - bounceStartTime)[0];
	newPos.z = MovingBody::computeTranslationEquation(bouncePos.z, z_moveSpeed, 0, glfwGetTime() - bounceStartTime)[0];
	if (newPos.y < 0.0f)
	{
		newPos.y = 0.0f;
		bouncePos = newPos;
		bounceCount++;
	}
	setPosAbsolute(newPos);
}
