#ifndef LANTERN_CLASS_H
#define LANTERN_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Model.h"

class Lantern : public Model
{
public:
	Lantern(std::string const& modelPath);

	virtual void Draw(Shader& shader) override;

	void makeProjectile(float launchSpeed);

private:
	bool isProjectile = false;
	float projectileStartTime = 0.0f;
	glm::vec3 launchedPos;

	bool isBouncing = false;
	int bounceCount = 0;
	int maxBounces = 2;
	float bounceSpeedMod = -0.5;
	float bounceSpeed = 0.0f;
	float bounceStartTime = 0.0f;
	glm::vec3 bouncePos;
	

	std::vector<float> speedComps = std::vector<float>(2, 0.0f);

	void doProjectileMov();
	void doBounces();
};

#endif
