#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Model.h"
#include "Camera.h"
#include "Lantern.h"
#include "PickUps.h"

struct SphereCollision {
    glm::vec3 origin;
    float radius;
    float squaredRadius;
};

class PlayerChar : public Model {
public:
    Camera camera;
    Lantern *lantern = nullptr;

protected:
    void setupColliders() override;

private:
    glm::vec3 lanternAnchorPoint;

    bool holdingLantern = true;
    float cameraDist;
    bool isLanternOn = true;

    void setupCamera();

    glm::vec3 cameraLookAtVector;
    bool isJumping = false;
    float jumpSpeed = 4.0f;

    float jumpStartTime = 0.0f;

    int score = 0;
    float maxBatery = 100.0f;
    float currentBatery = maxBatery;

    float batteryDecayRate = 5.0f;


    SphereCollision collider;

    void setupLantern();

    glm::vec3 getColliderPos();

    void doJump();

    static bool intersectRaySegmentSphere(glm::vec3 o, glm::vec3 d, glm::vec3 so, float squaredRadius, glm::vec3 &ip);

public:
    PlayerChar
            (
                    std::string const &playerCharPath,
                    std::string const &lanternPath,
                    float cameraDist,
                    glm::vec3 cameraLookAtVector
            );

    bool isDead = false;

    virtual void Draw(Shader &shader, Shader &mainShader);

    virtual void setPosAbsolute(glm::vec3 newPos) override;

    virtual void translateBy(glm::vec3 vector) override;

    virtual void setRotationAbsolute(float angle, glm::vec3 rotationAxis) override;

    virtual void rotateBy(float angle, glm::vec3 rotationAxis) override;

    void processInput(GLFWwindow *window, float width, float height, float deltaTime, std::vector<Model *> &vector);

    void updateLookAt(GLFWwindow *window, float width, float height, float deltaTime);

    void throwLantern(float launchSpeed);

    void pickupLantern();

    void pickupObject(PickUps *object);

    void jump();

    void doBatteryDecay(float deltaTime);

    float getBatteryPercent() const;

    bool handleCollision(Model *otherModel);

    void handleLanternWallCollision(std::vector<Model *> objectsInScene) const;

    void handleLanternCollision();

    glm::vec3 getLanternAnchorPoint();

    void collisions(std::vector<Model *> &vector);

    void setBatteryDecayRate(float rate);

    float getBatteryDecayRate();

    bool getIsLanternOn();

    void setIsLanternOn(bool power);
};

