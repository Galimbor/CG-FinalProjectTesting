#include "Lantern.h"
#include <glm/gtx/io.hpp>

Lantern::Lantern(std::string const &modelPath)
        : Model(modelPath) {
    setupColliders();
}

void Lantern::Draw(Shader &shader) {
    doProjectileMov();
    Model::Draw(shader);
}

void Lantern::makeProjectile(float launchSpeed) {
    trackedRotationMatrix = rotationMatrix;
    isFree = true;
    isProjectile = true;
    moveSpeed = launchSpeed;
    projectileStartTime = glfwGetTime();
    launchedPos = getPos();


    glm::vec2 frontPlanar = glm::vec2(getFrontVector().x, getFrontVector().z);
    glm::vec2 xAxis = glm::vec2(1.0f, 0.0f);
    float dotProduct = glm::dot(xAxis, frontPlanar);
    float xAxis_Magnitude = glm::length(xAxis);
    float frontPlanar_Magnitude = glm::length(frontPlanar);

    float angle = glm::acos(dotProduct / (xAxis_Magnitude * frontPlanar_Magnitude));
    if (frontPlanar.y > 0.0f) {
        angle = -angle;
    }

    speedComps[0] = glm::cos(angle) * moveSpeed;
    speedComps[1] = -glm::sin(angle) * moveSpeed;
}

void Lantern::pickUp() {
    isFree = false;
    rotationMatrix = trackedRotationMatrix;

    for (int i = 0; i < meshes.size(); i++) {
        meshes[0].rotationMatrix = trackedRotationMatrix;
    }
}

void Lantern::rotateBy(float angle, glm::vec3 rotationAxis) {
    if (!isFree) {
        Model::rotateBy(angle, rotationAxis);
    } else {
        trackedRotationMatrix = glm::rotate(trackedRotationMatrix, angle, rotationAxis);

    }
}

void Lantern::setupColliders() {
    glm::vec3 offset = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 dims = glm::vec3(2.0f, 2.0f, 2.0f);
//    Collider* col = new Collider(CollisionTypes::Overlap, offset, dims);
    Collider *col = new Collider(getMeshes().at(0), CollisionTypes::Overlap);
    colliders.push_back(col);
    displacement = new Collider(*col);

}

void Lantern::handleCollision(Model *otherModel) {
    CollisionResult result;
    for (int i = 0; i < colliders.size() && !result.isColliding; i++) {
        for (int j = 0; j < otherModel->colliders.size() && !result.isColliding; j++) {
            result = displacement->isColliding(otherModel->colliders[j]);
//            std::cout << "dis max" << displacement->getBoxDimentions() << result.xCollision<< std::endl;
//            std::cout << "dis start " << displacement->getBoxStart() << std::endl;
//            std::cout << "other max" << otherModel->colliders[j]->getBoxStart() << std::endl;
//            std::cout << "other start" << otherModel->colliders[j]->getBoxDimentions() << std::endl;
            if (result.isColliding && result.colType == CollisionTypes::Block) {
                xBlocked = result.xCollision;
                yBlocked = result.yCollision;
                zBlocked = result.zCollision;
            }
        }
    }
}

void Lantern::doProjectileMov() {
    if (isProjectile) {
        glm::vec3 newPos;
        float x_moveSpeed = speedComps[0];
        float z_moveSpeed = speedComps[1];
        if (!(xBlocked && yBlocked && zBlocked)) {
            newPos.x = MovingBody::computeTranslationEquation(launchedPos.x, x_moveSpeed, 0,
                                                              glfwGetTime() - projectileStartTime)[0];
            newPos.y = MovingBody::computeTranslationEquation(launchedPos.y, 0, -9.8f,
                                                              glfwGetTime() - projectileStartTime)[0];
            newPos.z = MovingBody::computeTranslationEquation(launchedPos.z, z_moveSpeed, 0,
                                                              glfwGetTime() - projectileStartTime)[0];
            midAirPos = newPos;
        } else {
//            std::cout << "newPos" << newPos << std::endl;
            newPos.y = MovingBody::computeTranslationEquation(launchedPos.y, 0, -9.8f,
                                                              glfwGetTime() - projectileStartTime)[0];
            newPos.x = midAirPos.x;
            newPos.z = midAirPos.z;
        }
        if (newPos.y < 0.0f) {
            newPos.y = 0.0f;
            isProjectile = false;
            if (!(xBlocked && yBlocked && zBlocked)) {
                isBouncing = true;
                bouncePos = newPos;
                bounceCount = 1;
                bounceSpeed = -MovingBody::computeTranslationEquation(launchedPos.y, 0, -9.8f,
                                                                      glfwGetTime() - projectileStartTime)[1];
                bounceStartTime = glfwGetTime();
            }
        }


//            std::cout << "No block ever\n";
//        std::cout << " new pos : " << newPos << std::endl;
        setPosAbsolute(newPos);
//        }        else {
//            std::cout << "pos blocked" << glm::vec3(launchedPos.x, newPos.y, launchedPos.z)<< std::endl;
//            setPosAbsolute(glm::vec3(launchedPos.x, newPos.y, launchedPos.z));
//        }        //std::cout << "newPos: " << newPos.x << " " << newPos.y << " " << newPos.z << "\n";
    }

    if (isBouncing) {
        doBounces();
        if (bounceCount > maxBounces) {
            isBouncing = false;
        }
    }
}

void Lantern::doBounces() {
    glm::vec3 newPos;
    float x_moveSpeed = speedComps[0] + speedComps[0] * bounceSpeedMod * bounceCount;
    float y_moveSpeed = bounceSpeed / (bounceCount + 1);
    float z_moveSpeed = speedComps[1] + speedComps[1] * bounceSpeedMod * bounceCount;
    if (!(xBlocked && yBlocked && zBlocked)) {
        newPos.x = MovingBody::computeTranslationEquation(bouncePos.x, x_moveSpeed, 0,
                                                          glfwGetTime() - bounceStartTime)[0];
        newPos.y = MovingBody::computeTranslationEquation(bouncePos.y, y_moveSpeed, -9.8f,
                                                          glfwGetTime() - bounceStartTime)[0];
        newPos.z = MovingBody::computeTranslationEquation(bouncePos.z, z_moveSpeed, 0,
                                                          glfwGetTime() - bounceStartTime)[0];
        midAirPos = newPos;
    } else {
        newPos.y = MovingBody::computeTranslationEquation(bouncePos.y, y_moveSpeed, -9.8f,
                                                          glfwGetTime() - bounceStartTime)[0];
        newPos.x = midAirPos.x;
        newPos.z = midAirPos.z;
    }
//    newPos.x = MovingBody::computeTranslationEquation(bouncePos.x, x_moveSpeed, 0, glfwGetTime() - bounceStartTime)[0];
//    newPos.y = MovingBody::computeTranslationEquation(bouncePos.y, y_moveSpeed, -9.8f,
//                                                      glfwGetTime() - bounceStartTime)[0];
//    newPos.z = MovingBody::computeTranslationEquation(bouncePos.z, z_moveSpeed, 0, glfwGetTime() - bounceStartTime)[0];
    if (newPos.y < 0.0f) {
        newPos.y = 0.0f;
        bouncePos = newPos;
        bounceCount++;
    }
    setPosAbsolute(newPos);
}
