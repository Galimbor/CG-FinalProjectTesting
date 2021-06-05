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
            GLint lightSpotCutOffLoc = glGetUniformLocation( mainShader->ID, "light.cutOff" );
            GLint lightSpotOuterCutOffLoc = glGetUniformLocation( mainShader->ID, "light.outerCutOff" );
            GLint viewPosLoc = glGetUniformLocation( mainShader->ID, "viewPos" );
            glUniform3f( lightPosLoc, Syrian->lantern->getPos().x, Syrian->lantern->getPos().y+2.2, Syrian->lantern->getPos().z);
            glUniform3f( lightSpotdirLoc, Syrian->lantern->getFrontVector().x,Syrian->lantern->getFrontVector().y-1,Syrian->lantern->getFrontVector().z);
            glUniform1f( lightSpotCutOffLoc, glm::cos( glm::radians( 9.5f ) ) );
            glUniform1f( lightSpotOuterCutOffLoc, glm::cos( glm::radians( 15.5f ) ) );
            glUniform3f( viewPosLoc, 0,0,3);
            // Set lights properties
            glUniform3f( glGetUniformLocation( mainShader->ID, "light.ambient" ),   0.6f, 0.6f, 0.6f );
            // We set the diffuse intensity a bit higher; note that the right lighting conditions differ with each lighting method and environment.
            // Each environment and lighting type requires some tweaking of these variables to get the best out of your environment.
            glUniform3f( glGetUniformLocation( mainShader->ID, "light.diffuse" ), 0.8f, 0.8f, 0.8f );
            glUniform3f( glGetUniformLocation( mainShader->ID, "light.specular" ), 1.0f, 1.0f, 1.0f );
            glUniform1f( glGetUniformLocation( mainShader->ID, "light.constant" ), 1.0f );
            glUniform1f( glGetUniformLocation( mainShader->ID, "light.linear" ), 0.09 );
            glUniform1f( glGetUniformLocation( mainShader->ID, "light.quadratic" ), 0.032 );
            glUniform1f( glGetUniformLocation( mainShader->ID, "material.shininess" ), 32.0f );


            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			float currentTime = glfwGetTime();
			DeltaTime = currentTime - previousFrameTime;
            previousFrameTime = currentTime;


            Syrian->processInput(window, width, height, getDeltaTime(), objectsInScene);
            Syrian->doBatteryDecay(getDeltaTime());
            playerShader->Activate();

            Syrian->Draw(*playerShader,*mainShader);
            mainShader->Activate();
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

	char SyrianModelPath[] = "Models/char.obj";
	char LanternModelPath[] = "Models/new_lanterna.obj";
	Syrian = new PlayerChar
	(
		SyrianModelPath,
		LanternModelPath,
		10.0f,
		glm::normalize(glm::vec3(-1, 1, 1))
	);
//	Syrian->scaleBy(glm::vec3(0.5f,0.5f,0.5f));

	//put other objects in scene
//	char RockModelPath[] = "Models/rockModel.obj";
//	char BatteryModelPath[] = "Models/rockModel.obj";
	char Maze1ModelPath[] = "Models/maze1.obj";
	char FloorModelPath[] = "Models/chao.obj";
    auto *maze1= new Maze(Maze1ModelPath);
//    char Maze2ModelPath[] = "Models/maze2.obj";
//    auto *maze2= new Maze(MazeModelPath);
    auto *floor= new Maze(FloorModelPath);
    objectsInScene.push_back(maze1);
//    objectsInScene.push_back(maze2);
    objectsInScene.push_back(floor);
//	pickup1->scaleBy(glm::vec3 (0.7,0.7,0.7));
//	auto *pickup2 = new PickUps(BatteryModelPath, 0.0f, 100.0f);
//	pickup2->scaleBy(glm::vec3 (0.7,0.7,0.7));
//	auto *pickup3 = new PickUps(BatteryModelPath, 0.0f, 100.0f);
//	pickup3->scaleBy(glm::vec3 (0.7,0.7,0.7));
//	auto *pickup4 = new PickUps(BatteryModelPath, 0.0f, 100.0f);
//	pickup4->scaleBy(glm::vec3 (0.7,0.7,0.7));

//    auto *pickup5 = new PickUps(MazeModelPath, 0.0f, 100.0f);
//    pickup5->scaleBy(glm::vec3 (20,20,20));
//    pickup5->translateBy(glm::vec3(0,1,0));

//    objectsInScene.push_back(pickup2);
//    objectsInScene.back()->setPosAbsolute(glm::vec3(6.0f, 0.0f, 0.0f));
//    objectsInScene.push_back(pickup3);
//    objectsInScene.back()->setPosAbsolute(glm::vec3(-3.0f, 0.0f, 3.0f));
//    objectsInScene.push_back(pickup4);
//	objectsInScene.back()->setPosAbsolute(glm::vec3(-6.0f, 0.0f, 0.0f));
//    	objectsInScene.push_back(pickup1);
//    objectsInScene.back()->setPosAbsolute(glm::vec3(0.0f, 0.0f, 0.0f));

//    objectsInScene.push_back(pickup5);
//    objectsInScene.back()->setPosAbsolute(glm::vec3(-20.0f, 0.0f, 0.0f));
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
