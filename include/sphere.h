#pragma once

#include<vector>
#include<glm/glm.hpp>
#include <VAO.h>
#include <EBO.h>
#include <shader.h>
#include "texture.h"


const float PI = 3.1415926f;

class Sphere
{
public:
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;

	std::vector<unsigned int> indices;
	std::vector<unsigned int> lineIndices;

	unsigned int sectorCount;
	unsigned int stackCount;
	float radius;

	Shader shader;
	VAO vao;

	// layout locations for the shaders
	int attribVert = 0;
	int attribTex = 1;
	int attribNorm = 2;


	void Init();
	void InitRender();
	void Draw(Shader& shader, Texture& texture);

	Sphere();
};
