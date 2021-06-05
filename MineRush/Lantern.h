#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Model.h"



class Lantern : public Model
{
public:
    Lantern(std::string const& modelPath);

    virtual void Draw(Shader& shader) override;

    void makeProjectile(float launchSpeed);
    void pickUp();

    virtual void rotateBy(float angle, glm::vec3 rotationAxis) override;
    void handleCollision(Model *otherModel);
    bool isInAir() const;

    float getInnerLightRadius();
    float getOuterLightRadius();
    void  setInnerLightRadius(float angle);
    void  setOuterLightRadius(float angle);


protected:
    virtual void setupColliders() override;

private:

    float innerLightRadius = 23.5f;
    float outerLightRadius = 30.5f;

    bool isFree = false;
    float projectileStartTime = 0.0f;
    bool isBouncing = false;
    glm::vec3 launchedPos;
    glm::vec3 midAirPos;
    bool isProjectile = false;
    int bounceCount = 0;
    int maxBounces = 2;
    float bounceSpeedMod = -0.5;
    float bounceSpeed = 0.0f;
    float bounceStartTime = 0.0f;
    glm::vec3 bouncePos;

    glm::mat4 trackedRotationMatrix = glm::mat4(1.0f);


    std::vector<float> speedComps = std::vector<float>(2, 0.0f);

    void doProjectileMov();
    void doBounces();


};


