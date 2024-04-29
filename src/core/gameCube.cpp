#include "gameCube.h"

GameCube::GameCube(glm::vec3 position, glm::vec3 size)
{
	this->position = position;
	this->size = size;
}

void GameCube::Draw(CubeRenderer* renderer, Texture texture)
{
	renderer->DrawCube(texture, this->position, this->size, this->rotationAxis, this->rotate, this->color);
}
