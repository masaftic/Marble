#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	unsigned int Width, Height;

	// texture format
	unsigned int Internal_Format;
	unsigned int Image_Format;

	// texture config
	unsigned int Wrap_S;
	unsigned int Wrap_T;
	unsigned int Filter_Min;
	unsigned int Filter_Max;

	Texture();

	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	void Bind();
	void Unbind();
	void Delete();
};
