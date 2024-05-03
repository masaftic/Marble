#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shader.h"

class Texture
{
public:
	GLuint ID;
	unsigned int width, height;

	// texture format
	unsigned int internal_Format;
	unsigned int image_Format;

	// texture config
	unsigned int wrap_S;
	unsigned int wrap_T;
	unsigned int filter_Min;
	unsigned int filter_Max;

	Texture();

	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	void Bind();
	void Unbind();
	void Delete();
};
