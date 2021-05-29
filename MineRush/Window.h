#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "PlayerChar.h"
#include "MovingBody.h"
#include "PickUps.h"

class Window
{
public:
	GLFWwindow* window = nullptr;
	Shader* mainShader = nullptr;

	PlayerChar* Syrian = nullptr;
	std::vector<MovingBody*> objectsInScene;


	Window();
	void doFrameLoop();
	float getDeltaTime();
	void getWindowDimentions(float& width, float& height);

private:
	float width = 800;
	float height = 800;

	float DeltaTime = 0.0f;
	float previousFrameTime = 0.0f;

	void setupScene();

	void destroy();
};

#endif