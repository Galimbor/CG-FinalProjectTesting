#include "PickUps.h"
#include "MovingBody.h"

void PickUps::setupColliders() {

    glm::vec3 offset = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 dims = glm::vec3(2.0f, 4.0f, 2.0f);
    auto *col = new Collider(getMeshes().at(0), CollisionTypes::Overlap, isBear);
    colliders.push_back(col);

}

PickUps::PickUps(std::string const &modelPath, float batteryCharge, int score, bool bear)
        : Model(modelPath) {
    rotSpeed = 2.0f;
    this->batteryCharge = batteryCharge;
    this->score = score;
    this->isBear = bear;
    setupColliders();
}

void PickUps::Draw(Shader &shader, float deltaTime) {
    glm::vec3 yAxis = glm::vec3(0.0f, 0.1f, 0.0f);
    rotateBySpeed(glm::radians(90.0f), yAxis, deltaTime);
    Model::Draw(shader, deltaTime);
}
