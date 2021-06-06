#pragma once

#include "Model.h"
#include "MovingBody.h"

class PickUps : public Model {
protected:
    void setupColliders() override;

private:
    float batteryCharge = 0.0f;
    int score = 0;

public:
    PickUps(std::string const &modelPath, float batteryCharge, int score);

    void Draw(Shader &shader, float deltaTime) override;

    float getBatteryCharge() const { return batteryCharge; }

    float getScore() const { return score; }
};
