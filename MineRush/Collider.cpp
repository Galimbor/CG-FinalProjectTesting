#include "Collider.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "Mesh.h"
#include <glm/gtx/io.hpp>

Collider::Collider(Mesh &mesh, CollisionTypes::Type type, bool isBear) {
    this->colType = type;
    this->max = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
    this->min = glm::vec3(INFINITY, INFINITY, INFINITY);
    this->isBear = isBear;

    // std::cout << size << std::endl;
    for (const auto &vertice : mesh.vertices) {
        if (vertice.Position.x > max.x)
            max.x = vertice.Position.x;
        if (vertice.Position.y > max.y)
            max.y = vertice.Position.y;
        if (vertice.Position.z > max.z)
            max.z = vertice.Position.z;
        if (vertice.Position.x < min.x)
            min.x = vertice.Position.x;
        if (vertice.Position.y < min.y)
            min.y = vertice.Position.y;
        if (vertice.Position.z < min.z)
            min.z = vertice.Position.z;

        if (debugDrawBox) {
            makeDrawableBox();
            setupDebug();
        }
        setBoxDimentions();
    }

}

Collider::Collider(CollisionTypes::Type type, glm::vec3 boxOffset, glm::vec3 boxDimentions) {
    this->colType = type;
    this->boxOffset = boxOffset;
    this->boxDimentions = boxDimentions;
    if (debugDrawBox) {
        makeDrawableBox(vertices, indices);
        setupDebug();
    }

}


CollisionResult Collider::isColliding(Collider *otherCollider) {
    CollisionResult result;
    glm::vec3 thisBoxStart = getBoxStart();
    glm::vec3 otherBoxStart = otherCollider->getBoxStart();

    float xThisDimention = thisBoxStart.x + this->boxDimentions.x;
    float xOtherDimention = otherBoxStart.x + otherCollider->boxDimentions.x;
    result.xCollision = xThisDimention >= otherBoxStart.x
                        && xOtherDimention >= thisBoxStart.x;

    result.yCollision = thisBoxStart.y + this->boxDimentions.y >= otherBoxStart.y
                        && otherBoxStart.y + otherCollider->boxDimentions.y >= thisBoxStart.y;

    result.zCollision = thisBoxStart.z + this->boxDimentions.z >= otherBoxStart.z
                        && otherBoxStart.z + otherCollider->boxDimentions.z >= thisBoxStart.z;

    result.isColliding = result.xCollision && result.yCollision && result.zCollision;
    result.colType = otherCollider->colType;
    result.isBear = otherCollider->getIsBear();
    return result;
}


void Collider::setPosAbsolute(glm::vec3 newPos) {
    parentPosition = newPos;
}

glm::vec3 Collider::getBoxStart() {
    return min + parentPosition;
}

void Collider::DrawDebug(Shader &shader) {
    if (debugDrawBox) {
        glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), parentPosition);
        shader.setMat4("model", ModelMatrix);
        vao->Bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        vao->Unbind();
    }
}

void Collider::makeDrawableBox() {
    vertices = std::vector<glm::vec3>(8);
    indices = std::vector<unsigned int>(36);

    vertices[0] = min;
    vertices[1] = glm::vec3(max.x, min.y, min.z);
    vertices[2] = glm::vec3(max.x, min.y, max.z);
    vertices[3] = glm::vec3(min.x, min.y, max.z);
    vertices[4] = glm::vec3(min.x, max.y, min.z);
    vertices[5] = glm::vec3(max.x, max.y, min.z);
    vertices[6] = glm::vec3(max.x, max.y, max.z);
    vertices[7] = glm::vec3(min.x, max.y, max.z);


    int count = 0;
    //top face (0-1-2-3)
    indices[count++] = 2;
    indices[count++] = 1;
    indices[count++] = 0;

    indices[count++] = 0;
    indices[count++] = 3;
    indices[count++] = 2;

    //face (4-5-6-7)
    indices[count++] = 4;
    indices[count++] = 5;
    indices[count++] = 6;

    indices[count++] = 4;
    indices[count++] = 6;
    indices[count++] = 7;

    //face (3-2-6-7)
    indices[count++] = 3;
    indices[count++] = 6;
    indices[count++] = 2;

    indices[count++] = 3;
    indices[count++] = 7;
    indices[count++] = 6;

    //face (2-1-5-6)
    indices[count++] = 2;
    indices[count++] = 6;
    indices[count++] = 5;

    indices[count++] = 5;
    indices[count++] = 1;
    indices[count++] = 2;

    //face (0-1-5-4)
    indices[count++] = 0;
    indices[count++] = 1;
    indices[count++] = 4;

    indices[count++] = 1;
    indices[count++] = 5;
    indices[count++] = 4;

    //face (3-0-4-7)
    indices[count++] = 0;
    indices[count++] = 4;
    indices[count++] = 3;

    indices[count++] = 4;
    indices[count++] = 7;
    indices[count++] = 3;
}


void Collider::makeDrawableBox(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices) {
    vertices = std::vector<glm::vec3>(8);
    indices = std::vector<unsigned int>(36);

    vertices[0] = getBoxStart();
    vertices[1] = getBoxStart() - glm::vec3(getBoxDimentions().x, 0.0f, 0.0f);
    vertices[2] = getBoxStart() - glm::vec3(getBoxDimentions().x, 0.0f, getBoxDimentions().z);
    vertices[3] = getBoxStart() - glm::vec3(0.0f, 0.0f, getBoxDimentions().z);
    vertices[4] = getBoxStart() - glm::vec3(0.0f, getBoxDimentions().y, 0.0f);
    vertices[5] = getBoxStart() - glm::vec3(getBoxDimentions().x, getBoxDimentions().y, 0.0f);
    vertices[6] = getBoxStart() - glm::vec3(getBoxDimentions().x, getBoxDimentions().y, getBoxDimentions().z);
    vertices[7] = getBoxStart() - glm::vec3(0.0f, getBoxDimentions().y, getBoxDimentions().z);


    int count = 0;
    //top face (0-1-2-3)
    indices[count++] = 2;
    indices[count++] = 1;
    indices[count++] = 0;

    indices[count++] = 0;
    indices[count++] = 3;
    indices[count++] = 2;

    //face (4-5-6-7)
    indices[count++] = 4;
    indices[count++] = 5;
    indices[count++] = 6;

    indices[count++] = 4;
    indices[count++] = 6;
    indices[count++] = 7;

    //face (3-2-6-7)
    indices[count++] = 3;
    indices[count++] = 6;
    indices[count++] = 2;

    indices[count++] = 3;
    indices[count++] = 7;
    indices[count++] = 6;

    //face (2-1-5-6)
    indices[count++] = 2;
    indices[count++] = 6;
    indices[count++] = 5;

    indices[count++] = 5;
    indices[count++] = 1;
    indices[count++] = 2;

    //face (0-1-5-4)
    indices[count++] = 0;
    indices[count++] = 1;
    indices[count++] = 4;

    indices[count++] = 1;
    indices[count++] = 5;
    indices[count++] = 4;

    //face (3-0-4-7)
    indices[count++] = 0;
    indices[count++] = 4;
    indices[count++] = 3;

    indices[count++] = 4;
    indices[count++] = 7;
    indices[count++] = 3;


}

void Collider::setupDebug() {
//    debugShader->Activate();
    vao = new VAO();
    vao->Bind();

    vbo = new VBO(&vertices[0].x, vertices.size() * sizeof(glm::vec3));

    ebo = new EBO(&indices[0], indices.size() * sizeof(unsigned int));

    //pos vertexes
    vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(glm::vec3), (void *) 0);

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
}

glm::vec3 Collider::getMax() {
    return this->max;
}

glm::vec3 Collider::getMin() {
    return this->min;
}

void Collider::setMin(glm::vec3 newMin) {
    min = newMin;
}


void Collider::setMax(glm::vec3 newMax) {
    max = newMax;
}


Collider::Collider(Collider &collider) {
    this->max = collider.getMax();
    this->min = collider.getMin();
    this->colType = collider.colType;
    this->boxDimentions = collider.boxDimentions;
}

glm::vec3 Collider::getBoxDimentions() {
    return parentPosition + max;
}

void Collider::setBoxDimentions() {
    boxDimentions = abs(max - min);
}

void Collider::setIsBear(bool state) {
    this->isBear = state;

}

bool Collider::getIsBear() {
    return isBear;
}

Collider::Collider() = default;




