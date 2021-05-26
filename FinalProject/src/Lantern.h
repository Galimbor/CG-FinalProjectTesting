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

	std::vector<float> speedComps = std::vector<float>(2, 0.0f);

	void doProjectileMov();
};

#endif
