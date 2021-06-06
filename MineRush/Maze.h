#pragma once

#include "Model.h"
#include "MovingBody.h"

class Maze : public Model {
protected:
    virtual void setupColliders() override;

private:
    float batteryCharge = 0.0f;
    int score = 0;

public:
    explicit Maze(std::string const &modelPath);

    void Draw(Shader &shader, float deltaTime) override;

    float getBatteryCharge() { return batteryCharge; }

    float getScore() { return score; }
};
