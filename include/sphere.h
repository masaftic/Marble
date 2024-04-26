#pragma once

#include<vector>
#include<glm/glm.hpp>
#include <VAO.h>
#include <EBO.h>
#include <shaderClass.h>



const float PI = 3.1415926;

class Sphere
{
public:
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;

	std::vector<unsigned int> indices;
	std::vector<unsigned int> lineIndices;

	int sectorCount;
	int stackCount;
	float radius;

	Shader shader;
	VAO vao;

	// layout locations for the shaders
	int attribVert = 0;
	int attribNorm = 1;
	int attribTex = 2;


	void Init();
	void InitRender();
	void Draw();

	Sphere(Shader& shader);
};
