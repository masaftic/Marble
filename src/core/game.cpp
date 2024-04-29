#include "game.h"
#include <camera.h>
#include <texture.h>
#include <VAO.h>
#include <cubeRenderer.h>
#include <resourceManager.h>
#include <gameLevel.h>
#include <GLFW/glfw3.h>
#include <iomanip>
#include <sphere.h>
#include <gameCube.h>


CubeRenderer* cubeRenderer;

Camera* camera;
Player* player;
Sphere* sphere;

Game::Game(unsigned int width, unsigned int height) : height(height), width(width), state(GAME_ACTIVE), keys()
{
	
}

Game::~Game()
{
	delete cubeRenderer;
	delete sphere;
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
	Shader shader = ResourceManager::LoadShader("resources/shaders/default.vert", "resources/shaders/default.frag", "cube");
	
	player = new Player(glm::vec3(0.0f, 1.5f, 0.0f), shader);
	camera = new Camera(this->width, this->height, glm::vec3(0.0f, 0.0f, 2.0f), player);
	// sphere = new Sphere(shader);

	// set renderer controls
	cubeRenderer = new CubeRenderer(shader);

	//// load textures
	ResourceManager::LoadTexture("resources/textures/rock.png", true, "rock");
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
	
	//// load levels
	
}

void Game::ProcessInput(GLFWwindow* window, float dt)
{
	if (this->state == GAME_ACTIVE)
	{	
		glm::vec3 cameraDirection = glm::vec3(player->position.x, 0.0f, player->position.z) - glm::vec3(camera->position.x, 0.0f, camera->position.z);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			player->direction = glm::normalize(cameraDirection);
			player->MoveForward();
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			player->direction = glm::normalize(cameraDirection);
			player->MoveBackward();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			player->direction = glm::normalize(cameraDirection);
			player->StrafeRight();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			player->direction = glm::normalize(cameraDirection);
			player->StrafeLeft();
		}
		camera->Inputs(window, dt);
	}
}


void Game::Update(float dt)
{
	player->Update(dt);
	
	auto v = player->velocity;
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << v.x << " " << v.y << " " << v.z << '\n';
}


void Game::Render()
{
	Shader cubeShader = ResourceManager::GetShader("cube");

	cubeShader.Use();
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	camera->SetMatrix(cubeShader, "camMatrix");


	Texture block_solid = ResourceManager::GetTexture("block_solid");
	Texture rock = ResourceManager::GetTexture("rock");

	GameCube cube1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	GameCube cube2(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	GameCube cube3(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	GameCube cube4(glm::vec3(5.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	cube4.color = glm::vec3(1.0f, 0.5f, 0.2f);

	cube1.Draw(cubeRenderer, block_solid);
	cube2.Draw(cubeRenderer, block_solid);
	cube3.Draw(cubeRenderer, block_solid);
	cube4.Draw(cubeRenderer, block_solid);

	player->Draw(rock);
}

