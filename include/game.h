#pragma once

#include <vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
// #include "gameLevel.h"
#include "glm/glm.hpp"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};


class Game
{
public:
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	// std::vector<GameLevel> Levels;
	unsigned int LevelNumber = 0;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void ProcessInput(GLFWwindow* window, float dt);
	void Update(float dt);

	void UpdateResolution(int width, int height);
	void Render();

};

