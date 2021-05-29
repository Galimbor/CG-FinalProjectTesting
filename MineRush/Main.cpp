#include "Window.h"

int main()
{
	//glfwInit();

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//
	//GLFWwindow* window = glfwCreateWindow(800, 800, "Mine-Rush: A Migrant Odyssey", NULL, NULL);
	//
	//if (window == NULL)
	//{
	//	std::cout << "Failed to create GLFW window" << std::endl;
	//	glfwTerminate();
	//	return -1;
	//}
	//glfwMakeContextCurrent(window);
	//gladLoadGL();
	//
	//glViewport(0, 0, 800, 800);

	//Shader shaderProgram("src/Shaders/default.vert", "src/Shaders/default.frag");

	//char mPath[] = "Models/rockModel.obj";

	//PlayerChar Syrian(mPath, mPath, 30.0f, glm::normalize(glm::vec3(-1, 1, 1)));

	//while (!glfwWindowShouldClose(window))
	//{
	//	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	shaderProgram.Activate();

	//	Syrian.processInput(window);
	//	Syrian.Draw(shaderProgram);
	//
	//	glfwSwapBuffers(window);
	//
	//	glfwPollEvents();
	//}

	//
	//shaderProgram.Delete();
	//
	//glfwDestroyWindow(window);
	//glfwTerminate();
	//return 0;

	Window window;
	window.doFrameLoop();
	return 0;
}