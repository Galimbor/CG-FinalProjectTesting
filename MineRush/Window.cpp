#include "Window.h"
#include "Maze.h"

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
            GLint lightPosLoc = glGetUniformLocation( mainShader->ID, "light.position" );
            GLint lightSpotdirLoc = glGetUniformLocation( mainShader->ID, "light.direction" );
            GLint viewPosLoc = glGetUniformLocation( mainShader->ID, "viewPos" );
            GLint lightSpotCutOffLoc = glGetUniformLocation( mainShader->ID, "light.cutOff" );
            GLint lightSpotOuterCutOffLoc = glGetUniformLocation( mainShader->ID, "light.outerCutOff" );
            glUniform1f( lightSpotCutOffLoc, glm::cos( glm::radians( Syrian->lantern->getInnerLightRadius() ) ) );
            glUniform1f( lightSpotOuterCutOffLoc, glm::cos( glm::radians( Syrian->lantern->getOuterLightRadius()) ) );
            glUniform3f( lightPosLoc, Syrian->lantern->getPos().x, Syrian->lantern->getPos().y, Syrian->lantern->getPos().z);
            glUniform3f( lightSpotdirLoc, Syrian->lantern->getFrontVector().x,Syrian->lantern->getFrontVector().y,Syrian->lantern->getFrontVector().z);

            glUniform3f( viewPosLoc, Syrian->getPos().x,Syrian->getPos().y + 0.8, Syrian->getPos().z);
            // Set lights properties
            glUniform3f( glGetUniformLocation( mainShader->ID, "light.ambient" ),   0.2f, 0.2f, 0.2f );
            // We set the diffuse intensity a bit higher; note that the right lighting conditions differ with each lighting method and environment.
            // Each environment and lighting type requires some tweaking of these variables to get the best out of your environment.
            glUniform3f( glGetUniformLocation( mainShader->ID, "light.diffuse" ), 0.8f, 0.8f, 0.8f );
            glUniform3f( glGetUniformLocation( mainShader->ID, "light.specular" ), 1.0f, 1.0f, 1.0f );
            glUniform1f( glGetUniformLocation( mainShader->ID, "light.constant" ), 1.0f );
            glUniform1f( glGetUniformLocation( mainShader->ID, "light.linear" ), 0.09f );
            glUniform1f( glGetUniformLocation( mainShader->ID, "light.quadratic" ), 0.032 );
            glUniform1f( glGetUniformLocation( mainShader->ID, "material.shininess" ), 32.0f );


//            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			float currentTime = glfwGetTime();
			DeltaTime = currentTime - previousFrameTime;
            previousFrameTime = currentTime;

            Syrian->processInput(window, width, height, getDeltaTime(), objectsInScene);
            processInput(window);
            Syrian->doBatteryDecay(getDeltaTime());
            playerShader->Activate();

            Syrian->Draw(*playerShader,*mainShader);
            mainShader->Activate();
            std::cout << Syrian->getBatteryPercent() << std::endl;
            Syrian->handleLanternWallCollision(objectsInScene);
            Syrian->camera.setActiveCamera(*playerShader,*mainShader);

            for (auto & i : objectsInScene)
			{
                i->Draw(*mainShader);
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
	mainShader = new Shader("Shaders/default.vert", "Shaders/default.frag");
	playerShader = new Shader("Shaders/player.vert","Shaders/player.frag");


	char SyrianModelPath[] = "Models/char_direita_000.obj";
	char LanternModelPath[] = "Models/lanterna_000.obj";
	Syrian = new PlayerChar
	(
		SyrianModelPath,
		LanternModelPath,
		10.0f,
		glm::normalize(glm::vec3(-1, 1, 1))
	);
//	Syrian->scaleBy(glm::vec3(0.5f,0.5f,0.5f));

	//put other objects in scene

	char MazeModelPath[] = "Models/parede_chao.obj";
	char Battery1ModelPath[] = "Models/pilha.obj";
	char Battery2ModelPath[] = "Models/pilha2.obj";
	char Battery3ModelPath[] = "Models/pilha3.obj";
	char Battery4ModelPath[] = "Models/pilha4.obj";
	char Battery5ModelPath[] = "Models/pilha5.obj";
	char Battery6ModelPath[] = "Models/pilha6.obj";
	char UrsoModelPath[] = "Models/urso.obj";

    auto *maze = new Maze(MazeModelPath);
    auto *urso = new PickUps(UrsoModelPath,0,9999);
    auto *pilha = new PickUps(Battery1ModelPath, 40.0f, 0);
    auto *pilha2 = new PickUps(Battery2ModelPath, 100.0f, 0);
    auto *pilha3 = new PickUps(Battery3ModelPath, 100.0f, 0);
    auto *pilha4 = new PickUps(Battery4ModelPath, 100.0f, 0);
    auto *pilha5 = new PickUps(Battery5ModelPath, 100.0f, 0);
    auto *pilha6 = new PickUps(Battery6ModelPath, 100.0f, 0);

    objectsInScene.push_back(maze);
    objectsInScene.push_back(urso);
    objectsInScene.push_back(pilha);
    objectsInScene.push_back(pilha2);
    objectsInScene.push_back(pilha3);
    objectsInScene.push_back(pilha4);
    objectsInScene.push_back(pilha5);
    objectsInScene.push_back(pilha6);
}

void Window::destroy() const
{
	mainShader->Delete();
	playerShader->Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}

//void Window::collisions()
//{
//	std::vector<Model*> newObjectsInScene = std::vector<Model*>(objectsInScene.size(), nullptr);
//	int count = 0;
//	std::cout << objectsInScene.size() << std::endl;
//	for (auto & i : objectsInScene)
//	{
//		if (!Syrian->handleCollision(i))
//		{
//			newObjectsInScene[count++] = i;
//		}
//		Syrian->lantern->handleCollision(i);
//	}
//
//	Syrian->handleLanternCollision();
//
//
//	objectsInScene = std::vector<Model*>(newObjectsInScene.begin(), newObjectsInScene.begin() + count);
//}


void
Window::processInput(GLFWwindow *window) const {
    {

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window,true);
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            Syrian->lantern->setInnerLightRadius(23.5f);
            Syrian->lantern->setOuterLightRadius(30.5f);
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            Syrian->lantern->setInnerLightRadius(12.5f);
            Syrian->lantern->setOuterLightRadius(20.5f);
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            Syrian->lantern->setInnerLightRadius(7.5f);
            Syrian->lantern->setOuterLightRadius(12.5f);
        }
    }
}