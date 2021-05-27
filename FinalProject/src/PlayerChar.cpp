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

glm::vec3 PlayerChar::getLanternAnchorPoint()
{
	return getRightVector() * 5.0f + glm::vec3(0.0f, 1.0f, 0.0f) + getPos();
}

void PlayerChar::doJump()
{
	if (isJumping)
	{
		glm::vec3 newPos;
		newPos.x = 0.0f;
		newPos.y = MovingBody::computeTranslationEquation(0, jumpSpeed, -9.8f, glfwGetTime() - jumpStartTime)[0];
		newPos.y = newPos.y - getPos().y;
		newPos.z = 0.0f;
		if (getPos().y + newPos.y <= 0.0f)
		{
			newPos.y = -getPos().y;
			isJumping = false;
		}
		//std::cout << "jump vector: " << newPos.x << " " << newPos.y << " " << newPos.z << "\n";
		translateBy(newPos);
	}
}

void PlayerChar::setupLantern()
{
	if (holdingLantern)
	{
		lantern->setPosAbsolute(lanternAnchorPoint);
	}
}

PlayerChar::PlayerChar(std::string const& playerCharPath, std::string const& lanternPath, float cameraDist, glm::vec3 cameraLookAtVector)
	: Model(playerCharPath)
{
	lantern = new Lantern(lanternPath);
	this->cameraDist = cameraDist;
	this->cameraLookAtVector = cameraLookAtVector;

	this->lanternAnchorPoint = getLanternAnchorPoint();

	setupLantern();
	setupCamera();
}

void PlayerChar::Draw(Shader& shader)
{
	doJump();
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

void PlayerChar::setRotationAbsolute(float angle, glm::vec3 rotationAxis)
{
	Model::setRotationAbsolute(angle, rotationAxis);
	if (holdingLantern)
	{
		lantern->setRotationAbsolute(angle, rotationAxis);
	}
}

void PlayerChar::rotateBy(float angle, glm::vec3 rotationAxis)
{
	Model::rotateBy(angle, rotationAxis);
	if (holdingLantern)
	{
		lantern->rotateBy(angle, rotationAxis);
	}
}

void PlayerChar::processInput(GLFWwindow* window, float width, float height, float deltaTime)
{
	if (!isDead)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			glm::vec3 front = getFrontVector();
			translateBySpeed(front, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			glm::vec3 back = -getFrontVector();
			translateBySpeed(back, deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			glm::vec3 right = getRightVector();
			translateBySpeed(right, deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			glm::vec3 left = -getRightVector();
			translateBySpeed(left, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			throwLantern(20.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			jump();
		}

		updateLookAt(window, width, height, deltaTime);
	}
}

void PlayerChar::updateLookAt(GLFWwindow* window, float width, float height, float deltaTime)
{
	std::vector<glm::vec3> castResults = camera.getMouseCast(window, width, height);

	glm::vec3 direction = castResults[0];
	glm::vec3 origin = castResults[1];

	//float magnitude = -(origin.y / direction.y);
	float magnitude = ( getPos().y - origin.y) / direction.y;

	float x = origin.x + direction.x * magnitude;
	float z = origin.z + direction.z * magnitude;


	glm::vec3 lookAtPoint = glm::vec3(x, 0.0f, z);
	lookAtPoint = lookAtPoint - getPos();

	float dotProduct = glm::dot(lookAtPoint, getFrontVector());
	glm::vec3 crossProduct = glm::cross(lookAtPoint, getFrontVector());
	float lP_Magnitude = glm::length(lookAtPoint);
	float fV_Magnitude = glm::length(getFrontVector());

	float angle = glm::acos(dotProduct / (lP_Magnitude * fV_Magnitude));
	if (angle < 0.01f)
		angle = 0.0f;

	//std::cout << "lookAtPoint: " << lookAtPoint.x << " " << lookAtPoint.y << " " << lookAtPoint.z << "\n";
	//std::cout << "origin: " << origin.x << " " << origin.y << " " << origin.z << "\n";
	//std::cout << "direction: " << direction.x << " " << direction.y << " " << direction.z << "\n";
	//std::cout << "angle: " << angle << "\n";
	if (crossProduct.y < 0)
		rotateBySpeed(angle, glm::vec3(0.0f, 1.0f, 0.0f), deltaTime);
	else
	{
		rotateBySpeed(-angle, glm::vec3(0.0f, 1.0f, 0.0f), deltaTime);
	}
	this->lanternAnchorPoint = getLanternAnchorPoint();
	setupLantern();
}

void PlayerChar::throwLantern(float launchSpeed)
{
	if (holdingLantern)
	{
		holdingLantern = false;
		lantern->makeProjectile(launchSpeed);
	}
}

void PlayerChar::jump()
{
	isJumping = true;
	jumpStartTime = glfwGetTime();
}

void PlayerChar::doBatteryDecay(float deltaTime)
{
	if (!isDead)
	{
		currentBatery = glm::clamp(currentBatery - batteryDecayRate * deltaTime, 0.0f, maxBatery);
		if (getBatteryPercent() <= 0.0f)
		{
			isDead = true;
		}
	}
}

float PlayerChar::getBatteryPercent()
{
	return currentBatery / maxBatery;
}
