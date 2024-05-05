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
	
	player = new Player(glm::vec3(0.0f, 1.5f, 0.0f));
	camera = new Camera(this->width, this->height, player);


	Cube::initRender();

	Cube cube1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	Cube cube2(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	Cube cube3(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	Cube cube4(glm::vec3(5.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	Cube cube5(glm::vec3(5.0f, 2.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	cubes.push_back(cube1);
	cubes.push_back(cube2);
	cubes.push_back(cube3);
	cubes.push_back(cube4);
	cubes.push_back(cube5);

	for (int i = 0; i < 1; i++) {
		Cube cube35(glm::vec3(5.0f, 2.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f));
		cubes.push_back(cube35);
	}

	//// load textures
	ResourceManager::LoadTexture("resources/textures/rock.png", true, "rock");
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
	
	//// load levels
	
}

void Game::Reset()
{
	player->position = glm::vec3(0.0f, 1.5f, 0.0f);
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


	auto v = player->velocity;
	std::cout << std::setprecision(2) << std::fixed;
	// std::cout << v.x << " " << v.y << " " << v.z << '\n';
}


void Game::Render()
{
	Shader shader = ResourceManager::GetShader("default");

	shader.Use();
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	camera->SetMatrix(shader, "camMatrix");

	Texture block_solid = ResourceManager::GetTexture("block_solid");
	Texture rock = ResourceManager::GetTexture("rock");


	for (int i = 0; i < cubes.size(); i++) {
		Cube::Draw(cubes[i], shader, block_solid);
	}

	player->Draw(shader, rock);
}


