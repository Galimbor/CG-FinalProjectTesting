#ifndef PLAYERCHAR_CLASS_H
#define PLAYERCHAR_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Model.h"
#include "Camera.h"
#include "Lantern.h"
#include "PickUps.h"

struct SphereCollision
{
	glm::vec3 origin;
	float radius;
	float squaredRadius;
};

class PlayerChar : public Model
{
protected:
	virtual void setupColliders() override;

private:
	Lantern* lantern = nullptr;
	glm::vec3 lanternAnchorPoint;
	bool holdingLantern = true;

	Camera camera;
	float cameraDist;
	glm::vec3 cameraLookAtVector;

	bool isJumping = false;
	float jumpSpeed = 10.0f;
	float jumpStartTime = 0.0f;

	int score = 0;

	float maxBatery = 100.0f;
	float currentBatery = maxBatery;
	float batteryDecayRate = 2.0f;

	bool isDead = false;

	SphereCollision collider;

	void setupCamera();

	void setupLantern();

	glm::vec3 getLanternAnchorPoint();
	glm::vec3 getColliderPos();

	void doJump();

	static bool intersectRaySegmentSphere(glm::vec3 o, glm::vec3 d, glm::vec3 so, float squaredRadius, glm::vec3& ip);

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

	void processInput(GLFWwindow* window, float width, float height, float deltaTime);

	void updateLookAt(GLFWwindow* window, float width, float height, float deltaTime);

	void throwLantern(float launchSpeed);
	void pickupLantern();
	void pickupObject(PickUps* object);

	void jump();

	void doBatteryDecay(float deltaTime);

	float getBatteryPercent();

	bool handleCollision(Model* otherModel);
	void handleLanternCollision();
};

#endif