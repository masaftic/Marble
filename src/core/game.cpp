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
}

void Game::Init()
{
	// load shaders
	Shader shader = ResourceManager::LoadShader("resources/shaders/default.vert", "resources/shaders/default.frag", "cube");
	
	camera = new Camera(this->Width, this->Height, glm::vec3(0.0f, 4.0f, 2.0f));
	player = new Player(glm::vec3(0.0f, 20.0f, 0.0f));
	camera->player = player;

	// set renderer controls
	Renderer = new CubeRenderer(shader);

	//// load textures
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
	
	//// load levels
	
}

void Game::ProcessInput(GLFWwindow* window, float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		camera->Inputs(window, dt);
	}
}

void Game::Update(float dt)
{
	
}

void Game::Render()
{
	Shader shader = ResourceManager::GetShader("cube");
	shader.Use();
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	camera->SetMatrix(shader, "camMatrix");

	Texture texture = ResourceManager::GetTexture("block_solid");

	Renderer->DrawCube(texture, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(30.0f, 1.0f, 30.0f));
	Renderer->DrawCube(texture, glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(30.0f, 1.0f, 30.0f));
	Renderer->DrawCube(texture, glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(30.0f, 1.0f, 30.0f));


	Renderer->DrawCube(texture, player->Pos, glm::vec3(10.0f, 10.0f, 10.0f));
}

