#pragma once

#include <glm/glm.hpp>
#include <cubeRenderer.h>

class GameCube
{
public:
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	float rotate = 0.0f;
	glm::vec3 color = glm::vec3(1.0f);

	GameCube(glm::vec3 position, glm::vec3 size);

	void Draw(CubeRenderer* renderer, Texture texture);
};

