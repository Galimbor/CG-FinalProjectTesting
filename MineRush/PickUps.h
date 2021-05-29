#ifndef PICKUPS_CLASS_H
#define PICKUPS_CLASS_H

#include "Model.h"
#include "MovingBody.h"

class PickUps : public Model
{
private:
	float batteryCharge = 0.0f;
	float score = 0.0f;

public:
	PickUps(std::string const& modelPath);
	virtual void Draw(Shader& shader, float deltaTime) override;
};
#endif
