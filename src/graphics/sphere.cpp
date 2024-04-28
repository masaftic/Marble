#include "sphere.h"
#include "glm/glm.hpp"

Sphere::Sphere(Shader& shader) : radius(1.0f), sectorCount(50), stackCount(40)
{
	this->radius = radius;
	this->sectorCount = sectorCount;
	this->stackCount = stackCount;
	this->shader = shader;
	this->shader.Use();
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
		}
	}

	for (int y = 0; y < this->stackCount; ++y)
	{
		for (int x = 0; x < this->sectorCount; ++x)
		{
			this->indices.push_back((y + 1) * (this->sectorCount + 1) + x);
			this->indices.push_back(y * (this->sectorCount + 1) + x);
			this->indices.push_back(y * (this->sectorCount + 1) + x + 1);

			this->indices.push_back((y + 1) * (this->sectorCount + 1) + x);
			this->indices.push_back(y * (this->sectorCount + 1) + x + 1);
			this->indices.push_back((y + 1) * (this->sectorCount + 1) + x + 1);
		}
	}

	// Calculate texture coordinates for each vertex
	for (size_t i = 0; i < this->vertices.size() / 3 - 2; i++) {
		glm::vec3 vertex = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);

		// Calculate spherical coordinates
		float theta = atan2(vertex.z, vertex.x);  // Longitude
		float phi = acos(vertex.y / radius);       // Latitude

		// Map spherical coordinates to texture coordinates
		float u = (theta + PI) / (2 * PI);
		float v = phi / PI;

		// Store texture coordinates
		this->texCoords.push_back(u);
		this->texCoords.push_back(v);
	}
}



void Sphere::InitRender()
{
	// auto vert = this->vertices;
	this->vao.Bind();
	VBO vbo(this->vertices.data(), (unsigned int)this->vertices.size() * sizeof(float));
	VBO vbotex(this->texCoords.data(), (unsigned int)this->texCoords.size() * sizeof(float));

	EBO ebo(this->indices.data(), (unsigned int)this->indices.size() * sizeof(int));

	int stride = 32 * sizeof(char);
	this->vao.LinkAtrrib(vbo, this->attribVert, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	this->vao.LinkAtrrib(vbotex, this->attribNorm, 3, GL_FLOAT, 2 * sizeof(float), (void*)(0));
	//this->vao.LinkAtrrib(vbo, this->attribTex, 2, GL_FLOAT, 8 * sizeof(float), (void*)(sizeof(float) * 6));

	vbo.Unbind();
	this->vao.Unbind();
	ebo.Unbind();
}


void Sphere::Draw()
{
	shader.Use();

	this->vao.Bind();
	glDrawElements(GL_TRIANGLES, (unsigned int)this->indices.size(), GL_UNSIGNED_INT, 0);
}

