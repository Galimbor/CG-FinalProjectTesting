#include "Window.h"
#include "Maze.h"


Window::Window() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Mine-Rush: A Migrant Odyssey", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, width, height);

    setupScene();

}

void Window::doFrameLoop() {
    if (window) {
        while (!glfwWindowShouldClose(window)) {
            GLint lightPosLoc = glGetUniformLocation(mainShader->ID, "light.position");
            GLint lightSpotdirLoc = glGetUniformLocation(mainShader->ID, "light.direction");
            GLint viewPosLoc = glGetUniformLocation(mainShader->ID, "viewPos");
            GLint lightSpotCutOffLoc = glGetUniformLocation(mainShader->ID, "light.cutOff");
            GLint lightSpotOuterCutOffLoc = glGetUniformLocation(mainShader->ID, "light.outerCutOff");
            glUniform1f(lightSpotCutOffLoc, glm::cos(glm::radians(Syrian->lantern->getInnerLightRadius())));
            glUniform1f(lightSpotOuterCutOffLoc, glm::cos(glm::radians(Syrian->lantern->getOuterLightRadius())));
            glUniform3f(lightPosLoc, Syrian->lantern->getPos().x-0.3f, Syrian->lantern->getPos().y + 0.5f,
                        Syrian->lantern->getPos().z);
            glUniform3f(lightSpotdirLoc, Syrian->lantern->getFrontVector().x, Syrian->lantern->getFrontVector().y,
                        Syrian->lantern->getFrontVector().z);

            glUniform3f(viewPosLoc, Syrian->getPos().x, Syrian->getPos().y + 0.8, Syrian->getPos().z);

//            glUniform1f(glGetUniformLocation(playerShader->ID, "light"), 1.0);

            // Set lights properties
            glUniform3f(glGetUniformLocation(mainShader->ID, "light.ambient"), 0.5, 0.5, 0.5);

            // We set the diffuse intensity a bit higher; note that the right lighting conditions differ with each lighting method and environment.
            // Each environment and lighting type requires some tweaking of these variables to get the best out of your environment.
            glUniform3f(glGetUniformLocation(mainShader->ID, "light.diffuse"), 0.9f, 0.9f, 0.9f);
            glUniform3f(glGetUniformLocation(mainShader->ID, "light.specular"), 1.0f, 1.0f, 1.0f);
            glUniform1f(glGetUniformLocation(mainShader->ID, "light.constant"), 1.0f);
            glUniform1f(glGetUniformLocation(mainShader->ID, "light.linear"), 0.09f);
            glUniform1f(glGetUniformLocation(mainShader->ID, "light.quadratic"), 0.032f);
            glUniform1f(glGetUniformLocation(mainShader->ID, "material.shininess"), 32.0f);
            glUniform1f(glGetUniformLocation(mainShader->ID, "flashlightIntensity"),
                        Syrian->getBatteryPercent() * Syrian->getBatteryDecayRate() / 5);


            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            float currentTime = glfwGetTime();
            DeltaTime = currentTime - previousFrameTime;
            previousFrameTime = currentTime;

            Syrian->processInput(window, width, height, getDeltaTime(), objectsInScene);
            processInput(window);
            Syrian->doBatteryDecay(getDeltaTime());
            playerShader->Activate();

            Syrian->Draw(*playerShader, *mainShader);
            mainShader->Activate();
            Syrian->handleLanternWallCollision(objectsInScene);
            Syrian->camera.setActiveCamera(*playerShader, *mainShader);

            for (auto &i : objectsInScene) {
                i->Draw(*mainShader);
            }

            glfwSwapBuffers(window);

            glfwPollEvents();

            if (Syrian->isDead) {
                std::cout << "===============================\n"
                             "          GAME OVER\n"
                             "Your battery ran out and you are stuck inside the mine forever\n"
                             "===============================\n";
                glfwSetWindowShouldClose(window, true);
            }
            if (Syrian->victory) {
                std::cout << "===============================\n"
                             "         CONGRATULATIONS\n"
                             "You were able to escape the mine and get back to your family, with " << Syrian->getScore()
                          << " pieces of gold\n"
                             "===============================\n";
                glfwSetWindowShouldClose(window, true);
            }
        }
        destroy();
    }
}

float Window::getDeltaTime() const {
    return DeltaTime;
}

void Window::getWindowDimentions(float &width, float &height) {
    width = this->width;
    height = this->height;
}

void Window::setupScene() {
    mainShader = new Shader("Shaders/default.vert", "Shaders/default.frag");
    playerShader = new Shader("Shaders/player.vert", "Shaders/player.frag");


    char SyrianModelPath[] = "Models/char_direita_000.obj";
    char LanternModelPath[] = "Models/lanterna_000.obj";
    Syrian = new PlayerChar
            (
                    SyrianModelPath,
                    LanternModelPath,
                    15.0f,
                    glm::normalize(glm::vec3(-1, 1, 1))
            );


    //put other objects in scene

    char MazeModelPath[] = "Models/maze_sem_chao.obj";
    char FloorModelPath[] = "Models/chao.obj";
    char Battery1ModelPath[] = "Models/battery1.obj";
    char Battery2ModelPath[] = "Models/battery2.obj";
    char Battery3ModelPath[] = "Models/battery3.obj";
    char Battery4ModelPath[] = "Models/battery4.obj";
    char Battery5ModelPath[] = "Models/battery5.obj";
    char Battery6ModelPath[] = "Models/battery6.obj";
    char Battery7ModelPath[] = "Models/battery7.obj";
    char UrsoModelPath[] = "Models/urso.obj";
    char Gold1ModelPath[] = "Models/ouro1.obj";
    char Gold2ModelPath[] = "Models/ouro2.obj";
    char Gold3ModelPath[] = "Models/ouro3.obj";
    char Gold4ModelPath[] = "Models/ouro4.obj";
    char Gold5ModelPath[] = "Models/ouro5.obj";

    auto *maze = new Maze(MazeModelPath);
    auto *floor = new Maze(FloorModelPath);
    auto *gold1 = new PickUps(Gold1ModelPath, 0, 1, false);
    auto *gold2 = new PickUps(Gold2ModelPath, 0, 1, false);
    auto *gold3 = new PickUps(Gold3ModelPath, 0, 1, false);
    auto *gold4 = new PickUps(Gold4ModelPath, 0, 1, false);
    auto *gold5 = new PickUps(Gold5ModelPath, 0, 1, false);
    auto *urso = new PickUps(UrsoModelPath, 0, 0, true);
    auto *pilha = new PickUps(Battery1ModelPath, 40.0f, 0, false);
    auto *pilha2 = new PickUps(Battery2ModelPath, 100.0f, 0, false);
    auto *pilha3 = new PickUps(Battery3ModelPath, 100.0f, 0, false);
    auto *pilha4 = new PickUps(Battery4ModelPath, 100.0f, 0, false);
    auto *pilha5 = new PickUps(Battery5ModelPath, 100.0f, 0, false);
    auto *pilha6 = new PickUps(Battery6ModelPath, 100.0f, 0, false);
    auto *pilha7 = new PickUps(Battery7ModelPath, 100.0f, 0, false);

    objectsInScene.push_back(maze);
    objectsInScene.push_back(floor);
    objectsInScene.push_back(urso);
    objectsInScene.push_back(gold1);
    objectsInScene.push_back(gold2);
    objectsInScene.push_back(gold3);
    objectsInScene.push_back(gold4);
    objectsInScene.push_back(gold5);
    objectsInScene.push_back(pilha);
    objectsInScene.push_back(pilha2);
    objectsInScene.push_back(pilha3);
    objectsInScene.push_back(pilha4);
    objectsInScene.push_back(pilha5);
    objectsInScene.push_back(pilha6);
    objectsInScene.push_back(pilha7);
}

void Window::destroy() const {
    mainShader->Delete();
    playerShader->Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
}


void
Window::processInput(GLFWwindow *window) {
    {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            Window::setupScene();
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            Syrian->lantern->setInnerLightRadius(23.5f);
            Syrian->lantern->setOuterLightRadius(30.5f);
            Syrian->setBatteryDecayRate(5.0f);
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            Syrian->lantern->setInnerLightRadius(12.5f);
            Syrian->lantern->setOuterLightRadius(20.5f);
            Syrian->setBatteryDecayRate(3.5f);
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            Syrian->lantern->setInnerLightRadius(7.5f);
            Syrian->lantern->setOuterLightRadius(12.5f);
            Syrian->setBatteryDecayRate(2.0f);
        }
    }
}