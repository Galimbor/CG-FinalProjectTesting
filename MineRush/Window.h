#pragma once

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "PlayerChar.h"
#include "MovingBody.h"
#include "PickUps.h"

class Window {
public:
    GLFWwindow *window = nullptr;
    Shader *mainShader = nullptr;
    Shader *playerShader = nullptr;

    PlayerChar *Syrian = nullptr;
    std::vector<Model *> objectsInScene;


    Window();

    void doFrameLoop();

    float getDeltaTime() const;


    void getWindowDimentions(float &width, float &height);

private:
    //float width = 800;
    float width = 1920;
    //float height = 800;
    float height = 1080;

    float DeltaTime = 0.0f;
    float previousFrameTime = 0.0f;

    void setupScene();

    void destroy() const;

//	void collisions();

    void processInput(GLFWwindow *window);
};

