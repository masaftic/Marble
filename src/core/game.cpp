#include "game.h"
#include <camera.h>
#include <texture.h>
#include <VAO.h>
#include <cubeRenderer.h>
#include <resourceManager.h>
#include <gameLevel.h>
#include <GLFW/glfw3.h>

CubeRenderer* Renderer;

Camera* camera;
Player* player;


Game::Game(unsigned int width, unsigned int height) : Height(height), Width(width), State(GAME_ACTIVE), Keys()
{
	
}

Game::~Game()
{
	delete Renderer;
	delete player;
	delete camera;
}

void Game::Init()
{
	// load shaders
	Shader shader = ResourceManager::LoadShader("resources/shaders/default.vert", "resources/shaders/default.frag", "cube");
	
	player = new Player(glm::vec3(0.0f, 20.0f, 0.0f));
	camera = new Camera(this->Width, this->Height, glm::vec3(0.0f, 4.0f, 2.0f), player);

	// set renderer controls
	Renderer = new CubeRenderer(shader);

	//// load textures
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("resources/textures/block.png", false, "block");
	
	//// load levels
	
}

void Game::ProcessInput(GLFWwindow* window, float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		// camera direction
		glm::vec3 cameraDirection = glm::vec3(player->Position.x, 0.0f, player->Position.z) - glm::vec3(camera->Position.x, 0.0f, camera->Position.z);
		player->Direction = glm::normalize(cameraDirection);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			player->MoveForward();
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			player->MoveBackward();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			player->StrafeRight();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			player->StrafeLeft();

		}		
		camera->Inputs(window, dt);
	}
}

void Game::Update(float dt)
{
	player->Update(dt);
}

void Game::Render()
{
	Shader shader = ResourceManager::GetShader("cube");
	shader.Use();
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	camera->SetMatrix(shader, "camMatrix");

	Texture texture = ResourceManager::GetTexture("block_solid");
	Texture texture2 = ResourceManager::GetTexture("block");

	Renderer->DrawCube(texture, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(30.0f, 1.0f, 30.0f));
	Renderer->DrawCube(texture, glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(30.0f, 1.0f, 30.0f));
	Renderer->DrawCube(texture, glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(30.0f, 1.0f, 30.0f));


	Renderer->DrawCube(texture2, player->Position, glm::vec3(10.0f, 10.0f, 10.0f));
}

