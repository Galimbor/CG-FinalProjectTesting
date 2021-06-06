#include "PickUps.h"
#include "MovingBody.h"

void PickUps::setupColliders() {

    glm::vec3 offset = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 dims = glm::vec3(2.0f, 4.0f, 2.0f);
//    auto* col = new Collider(CollisionTypes::Type::Overlap,offset,dims);
//    colliders.push_back(col);
    auto *col = new Collider(getMeshes().at(0), CollisionTypes::Overlap);
    colliders.push_back(col);

}

PickUps::PickUps(std::string const &modelPath, float batteryCharge, int score)
        : Model(modelPath) {
    rotSpeed = 2.0f;
    setupColliders();
    this->batteryCharge = batteryCharge;
    this->score = score;
}

void PickUps::Draw(Shader &shader, float deltaTime) {
    glm::vec3 yAxis = glm::vec3(0.0f, 0.1f, 0.0f);
    rotateBySpeed(glm::radians(90.0f), yAxis, deltaTime);
    Model::Draw(shader, deltaTime);
}
