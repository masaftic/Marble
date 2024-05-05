#include "sphere.h"
#include "glm/glm.hpp"
#include <texture.h>

Sphere::Sphere() : radius(1.0f), sectorCount(200), stackCount(200)
{
	this->radius = radius;
	this->sectorCount = sectorCount;
	this->stackCount = stackCount;
	this->Init();
	this->InitRender();
}

void Sphere::Init()
{

	for (unsigned int y = 0; y <= this->stackCount; ++y)
	{
		for (unsigned int x = 0; x <= this->sectorCount; ++x)
		{
			float xSegment = (float)x / (float)this->sectorCount;
			float ySegment = (float)y / (float)this->stackCount;
			float xPos = this->radius * std::cos(xSegment * 2 * PI) * std::sin(ySegment * PI);
			float yPos = this->radius * std::cos(ySegment * PI);
			float zPos = this->radius * std::sin(xSegment * 2 * PI) * std::sin(ySegment * PI);

			this->vertices.push_back(xPos);
			this->vertices.push_back(yPos);
			this->vertices.push_back(zPos);


			this->texCoords.push_back(xSegment);
			this->texCoords.push_back(ySegment);

			// Calculate the vertex normal
			float nx = xPos / this->radius;
			float ny = yPos / this->radius;
			float nz = zPos / this->radius;

			this->normals.push_back(nx);
			this->normals.push_back(ny);
			this->normals.push_back(nz);
		}
	}

	for (unsigned int y = 0; y <= this->stackCount; ++y)
	{
		for (unsigned int x = 0; x <= this->sectorCount; ++x)
		{
			this->indices.push_back((y + 1) * (this->sectorCount + 1) + x);
			this->indices.push_back(y * (this->sectorCount + 1) + x);
			this->indices.push_back(y * (this->sectorCount + 1) + x + 1);

			this->indices.push_back((y + 1) * (this->sectorCount + 1) + x);
			this->indices.push_back(y * (this->sectorCount + 1) + x + 1);
			this->indices.push_back((y + 1) * (this->sectorCount + 1) + x + 1);
		}
	}
}



void Sphere::InitRender()
{
	this->vao.Bind();
	VBO vbo(this->vertices.data(), (unsigned int)this->vertices.size() * sizeof(float));
	VBO vbotex(this->texCoords.data(), (unsigned int)this->texCoords.size() * sizeof(float));

	EBO ebo(this->indices.data(), (unsigned int)this->indices.size() * sizeof(int));

	this->vao.LinkAtrrib(vbo, this->attribVert, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	this->vao.LinkAtrrib(vbotex, this->attribTex, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	// this->vao.LinkAtrrib(vbotex, this->attribNorm, 3, GL_FLOAT, 2 * sizeof(float), (void*)(0));

	vbotex.Unbind();
	vbo.Unbind();
	this->vao.Unbind();
	ebo.Unbind();
}



void Sphere::Draw(Shader& shader, Texture& texture)
{
	shader.Use();

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	this->vao.Bind();
	glDrawElements(GL_TRIANGLES, (unsigned int)this->indices.size(), GL_UNSIGNED_INT, 0);
}

