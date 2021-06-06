#include "Maze.h"
#include "MovingBody.h"

void Maze::setupColliders() {
    for (int i = 0; i < getMeshes().size(); ++i) {
        auto *col = new Collider(getMeshes().at(i), CollisionTypes::Block);
        colliders.push_back(col);
    }

}

Maze::Maze(std::string const &modelPath)
        : Model(modelPath) {
    rotSpeed = 2.0f;
    setupColliders();
}

void Maze::Draw(Shader &shader, float deltaTime) {
    Model::Draw(shader, deltaTime);
}
