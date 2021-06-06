#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"

namespace CollisionTypes {
    enum Type {
        Block,
        Overlap,
        None
    };
};

struct CollisionResult {
    CollisionTypes::Type colType;
    bool isColliding = false;

    bool xCollision = false;
    bool yCollision = false;
    bool zCollision = false;
};

class Collider {

private:
    glm::vec3 max;
    glm::vec3 min;

    glm::vec3 boxDimentions;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    //Shader* debugShader;
    class VAO *vao = nullptr;

    class VBO *vbo = nullptr;

    class EBO *ebo = nullptr;

    CollisionTypes::Type colType;

    glm::vec3 boxOffset;
    glm::vec3 parentPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    void makeDrawableBox(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);

    void setupDebug();

    void makeDrawableBox();

public:


    Collider(class Mesh &mesh, CollisionTypes::Type type);

    Collider();

    Collider(Collider &collider);


    bool debugDrawBox = false;

    Collider(CollisionTypes::Type type, glm::vec3 boxOffset, glm::vec3 boxDimentions);

    CollisionResult isColliding(Collider *otherCollider);

    std::vector<Collider> getAllCollisions(std::vector<Collider> allHitBoxes);

    void setPosAbsolute(glm::vec3 newPos);

    glm::vec3 getMax();

    glm::vec3 getMin();

    void setMax(glm::vec3 newMax);

    void setMin(glm::vec3 newMin);

    glm::vec3 getBoxStart();

    void DrawDebug(Shader &shader);

    glm::vec3 getBoxDimentions();

    void setBoxDimentions();

};