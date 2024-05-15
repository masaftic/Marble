#pragma once

#include <glm/glm.hpp>
#include "VAO.h"
#include "shader.h"
#include "texture.h"

class Cube
{
public:
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	float rotate = 0.0f;
	glm::vec3 color = glm::vec3(1.0f);
	bool isEnd = 0;

	Cube(glm::vec3 position, glm::vec3 size);
	Cube(const Cube& other);

	static VAO* vao;

	static void initRender();
	void Draw(Shader& shader, Texture& texture);
};

