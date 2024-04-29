#pragma once
#include <shaderClass.h>
#include <texture.h>
#include <glm/glm.hpp>
#include "VAO.h"


class CubeRenderer
{
public:
	CubeRenderer(Shader& shader);
	~CubeRenderer();

	void DrawCube(Texture& texture,
					glm::vec3 position,
					glm::vec3 size = glm::vec3(10.0f, 10.0f, 1.0f),
					glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f),
					float rotate = 0.0f,
					glm::vec3 color = glm::vec3(1.0f));

private:

	Shader shader;
	VAO cubeVAO;

	void initRenderData();
};
