#include "texture.h"

Texture::Texture() : width(0), height(0), internal_Format(GL_RGB), 
					 image_Format(GL_RGB), wrap_S(GL_CLAMP_TO_EDGE), 
	                 wrap_T(GL_CLAMP_TO_EDGE), filter_Min(GL_NEAREST),
	                 filter_Max(GL_NEAREST)
{
	// Generates an OpenGL texture object
	glGenTextures(1, &this->ID);
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
	this->width = width;
	this->height = height;

	this->Bind();

	// create texture	
	glTexImage2D(GL_TEXTURE_2D, 0, this->internal_Format, width, height, 0, this->image_Format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// set texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_Max);

	// unbind texture
	this->Unbind();
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &this->ID);
}
