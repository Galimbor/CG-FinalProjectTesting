#ifndef PICKUPS_CLASS_H
#define PICKUPS_CLASS_H

#include "Model.h"
#include "MovingBody.h"

class PickUps : public Model
{
protected:
	virtual void setupColliders() override;
private:
	float batteryCharge = 0.0f;
	int score = 0;

public:
	PickUps(std::string const& modelPath, float batteryCharge, int score);
	virtual void Draw(Shader& shader, float deltaTime) override;

	float getBatteryCharge() { return batteryCharge; }
	float getScore() { return score; }
};
#endif
