#pragma once

#include <vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
// #include "gameLevel.h"
#include "glm/glm.hpp"
#include "cube.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};


class Game
{
public:
	GameState state;
	bool keys[1024];
	unsigned int width, height;
	// std::vector<GameLevel> Levels;
	unsigned int levelNumber = 0;

	std::vector<Cube> cubes;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void Reset();
	void ProcessInput(GLFWwindow* window, float dt);
	void Update(float dt);

	void UpdateResolution(int width, int height);
	void Render();


};

