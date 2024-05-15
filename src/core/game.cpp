#include "game.h"
#include <camera.h>
#include <texture.h>
#include <VAO.h>
#include <resourceManager.h>
#include <gameLevel.h>
#include <GLFW/glfw3.h>
#include <iomanip>
#include <sphere.h>
#include <cube.h>



Camera* camera;
Player* player;

Cube* skyboxCube;
Cube* lightSource;
glm::vec4 lightColor;

Game::Game(unsigned int width, unsigned int height) : height(height), width(width), state(GAME_ACTIVE), keys()
{
	
}

Game::~Game()
{
	delete player;
	delete camera;
}

void Game::UpdateResolution(int width, int height)
{
	this->width = width;
	this->height = height;
	camera->width = width;
	camera->height = height;
}


void Game::Init()
{
	// load shaders
	Shader shader = ResourceManager::LoadShader("resources/shaders/default.vert", "resources/shaders/default.frag", "default");
	
	ResourceManager::LoadShader("resources/shaders/skybox.vert", "resources/shaders/skybox.frag", "skybox");

	ResourceManager::LoadShader("resources/shaders/light.vert", "resources/shaders/light.frag", "light");


	player = new Player(glm::vec3(0.0f, 1.5f, 0.0f));
	camera = new Camera(this->width, this->height, player);
	skyboxCube = new Cube(glm::vec3(0), glm::vec3(10000));
	lightSource = new Cube(glm::vec3(0), glm::vec3(0));
	// light source direction is set in the fragment shader because it is like a sun not a point

	lightColor = glm::vec4(1.0, 1.0, 0.95, 1.0f);

	Cube::initRender();

	cubes.push_back(Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f)));
	cubes.push_back(Cube(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f)));
	cubes.push_back(Cube(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f)));
	cubes.push_back(Cube(glm::vec3(5.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f)));
	cubes.push_back(Cube(glm::vec3(5.0f, 2.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f)));

	glm::vec3 poss = glm::vec3(5.0f, 2.0f, 5.0f);

	for (int ringSize = 6; ringSize > 0; ringSize--) {
		for (int i = 0; i < ringSize; i++) {
			poss.x += 5;
			cubes.push_back(Cube(poss, glm::vec3(5.0f, 1.0f, 5.0f)));
		}

		for (int i = 0; i < ringSize; i++) {
			poss.z += 5;
			cubes.push_back(Cube(poss, glm::vec3(5.0f, 1.0f, 5.0f)));
		}

		for (int i = 0; i < ringSize; i++) {
			poss.x -= 5;
			cubes.push_back(Cube(poss, glm::vec3(5.0f, 1.0f, 5.0f)));
		}

		for (int i = 0; i < ringSize; i++) {
			poss.z -= 5;
			cubes.push_back(Cube(poss, glm::vec3(5.0f, 1.0f, 5.0f)));
		}
		poss.x += 10;
		poss.z += 10;
		poss.y += 2;
	}



	//// load textures
	ResourceManager::LoadTexture("resources/textures/rock.png", true, "rock");
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("resources/textures/checkers.png", true, "checkers");

	std::vector<const char*> files = {
		"resources/textures/skybox/right.jpg",
		"resources/textures/skybox/left.jpg",
		"resources/textures/skybox/top.jpg",
		"resources/textures/skybox/bottom.jpg",
		"resources/textures/skybox/front.jpg",
		"resources/textures/skybox/back.jpg",
	};

	ResourceManager::LoadTextureCubeMap(files, "skybox");
	
	//// load levels
	
}

void Game::Reset()
{
	player->position = glm::vec3(0.0f, 1.5f, 0.0f);
	player->velocity = glm::vec3(0);

}


void Game::ProcessInput(GLFWwindow* window, float dt)
{
	if (this->state == GAME_ACTIVE)
	{	
		glm::vec3 cameraDirection = glm::vec3(player->position.x, 0.0f, player->position.z) - glm::vec3(camera->position.x, 0.0f, camera->position.z);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			player->direction = glm::normalize(cameraDirection);
			player->MoveForward(dt);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			player->direction = glm::normalize(cameraDirection);
			player->MoveBackward(dt);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			player->direction = glm::normalize(cameraDirection);
			player->StrafeRight(dt);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			player->direction = glm::normalize(cameraDirection);
			player->StrafeLeft(dt);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			player->Jump();
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			Reset();
		}
		camera->Inputs(window, dt);
	}
}



void Game::Update(float dt)
{	
	player->Update(dt, cubes);
	if (player->position.y < -10) {
		Reset();
	}
}


void Game::Render()
{
	Texture block_solid = ResourceManager::GetTexture("block_solid");
	Texture rock = ResourceManager::GetTexture("rock");
	Texture skyboxTexture = ResourceManager::GetTexture("skybox");

	Shader defaultShader = ResourceManager::GetShader("default");
	Shader lightShader = ResourceManager::GetShader("light");
	Shader skyboxShader = ResourceManager::GetShader("skybox");

	

	skyboxShader.Use();
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	camera->SetMatrix(skyboxShader, "camMatrix");

	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);
	skyboxCube->Draw(skyboxShader, skyboxTexture);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);




	lightShader.Use();
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	camera->SetMatrix(lightShader, "camMatrix");
	lightShader.setVec4("lightColor", lightColor);

	lightSource->Draw(lightShader, block_solid);




	defaultShader.Use();
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	camera->SetMatrix(defaultShader, "camMatrix");
	defaultShader.setVec4("lightColor", lightColor);
	defaultShader.setVec3("lightPos", lightSource->position);
	defaultShader.setVec3("camPos", camera->position);

	for (int i = 0; i < cubes.size(); i++) {
		cubes[i].Draw(defaultShader, block_solid);
	}

	player->Draw(defaultShader, rock);
}


