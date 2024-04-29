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


CubeRenderer* Renderer;

Camera* camera;
Player* player;
Sphere* sphere;

Game::Game(unsigned int width, unsigned int height) : Height(height), Width(width), State(GAME_ACTIVE), Keys()
{
	
}

Game::~Game()
{
	delete Renderer;
	delete sphere;
	delete player;
	delete camera;
}

void Game::UpdateResolution(int width, int height)
{
	this->Width = Width;
	this->Height = Height;
	camera->width = width;
	camera->height = height;
}


void Game::Init()
{
	// load shaders
	Shader shader = ResourceManager::LoadShader("resources/shaders/default.vert", "resources/shaders/default.frag", "cube");
	
	player = new Player(glm::vec3(0.0f, 1.5f, 0.0f), shader);
	camera = new Camera(this->Width, this->Height, glm::vec3(0.0f, 0.0f, 2.0f), player);
	// sphere = new Sphere(shader);

	// set renderer controls
	Renderer = new CubeRenderer(shader);

	//// load textures
	ResourceManager::LoadTexture("resources/textures/rock.png", true, "rock");
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
	
	
	//// load levels
	
}

void Game::ProcessInput(GLFWwindow* window, float dt)
{
	if (this->State == GAME_ACTIVE)
	{	
		glm::vec3 cameraDirection = glm::vec3(player->Position.x, 0.0f, player->Position.z) - glm::vec3(camera->Position.x, 0.0f, camera->Position.z);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			player->Direction = glm::normalize(cameraDirection);
			player->MoveForward();
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			player->Direction = glm::normalize(cameraDirection);
			player->MoveBackward();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			player->Direction = glm::normalize(cameraDirection);
			player->StrafeRight();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			player->Direction = glm::normalize(cameraDirection);
			player->StrafeLeft();
		}
		camera->Inputs(window, dt);
	}
}


void Game::Update(float dt)
{
	player->Update(dt);
	
	auto v = player->Velocity;
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

	Renderer->DrawCube(block_solid, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	Renderer->DrawCube(block_solid, glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	Renderer->DrawCube(block_solid, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f));
	Renderer->DrawCube(block_solid, glm::vec3(5.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f));

	player->Draw(rock);
	// Renderer->DrawCube(texture2, player->Position, glm::vec3(10.0f, 10.0f, 10.0f), glm::cross(player->Direction, glm::vec3(0.0f, 1.0f, 0.0f)), player->Rotation, glm::vec3(0.7f, 0.6f, 0.7f));
	
}

