#include "Window.h"

Window::Window()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Mine-Rush: A Migrant Odyssey", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, width, height);

	setupScene();
}

void Window::doFrameLoop()
{
	if (window)
	{
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			float currentTime = glfwGetTime();
			DeltaTime = currentTime - previousFrameTime;
			previousFrameTime = currentTime;

			mainShader->Activate();

			Syrian->processInput(window, width, height, getDeltaTime());
			Syrian->doBatteryDecay(getDeltaTime());
			Syrian->Draw(*mainShader);

			for (int i = 0; i < objectsInScene.size(); i++)
			{
				objectsInScene[i]->Draw(*mainShader, getDeltaTime());
			}

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
		destroy();
	}
}

float Window::getDeltaTime()
{
	return DeltaTime;
}

void Window::getWindowDimentions(float& width, float& height)
{
	width = this->width;
	height = this->height;
}

void Window::setupScene()
{
	mainShader = new Shader("src/Shaders/default.vert", "src/Shaders/default.frag");

	char SyrianModelPath[] = "Models/rockModel.obj";
	char LanternModelPath[] = "Models/gold.obj";
	Syrian = new PlayerChar
	(
		SyrianModelPath,
		LanternModelPath,
		30.0f,
		glm::normalize(glm::vec3(-1, 1, 1))
	);

	//put other objects in scene
	char RockModelPath[] = "Models/rockModel.obj";
	objectsInScene.push_back(new PickUps(RockModelPath));
	objectsInScene.back()->setPosAbsolute(glm::vec3(3.0f, 3.0f, 3.0f));
}

void Window::destroy()
{
	mainShader->Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}
