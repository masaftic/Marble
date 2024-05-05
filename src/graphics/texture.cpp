#include "texture.h"

Texture::Texture() : width(0), height(0), internal_Format(GL_RGB), 
					 image_Format(GL_RGB), wrap_S(GL_CLAMP_TO_EDGE), 
	                 wrap_T(GL_CLAMP_TO_EDGE), filter_Min(GL_NEAREST),
	                 filter_Max(GL_NEAREST),
					 textureType(GL_TEXTURE_2D)
{
	// Generates an OpenGL texture object
	glGenTextures(1, &this->ID);
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
	this->textureType = GL_TEXTURE_2D;
	this->width = width;
	this->height = height;

	this->Bind();

	// create texture	
	glTexImage2D(textureType, 0, this->internal_Format, width, height, 0, this->image_Format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(textureType);

	// set texture wrap and filter modes
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, this->wrap_S);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, this->wrap_T);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_R, this->wrap_T);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, this->filter_Min);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, this->filter_Max);

	// unbind texture
	this->Unbind();
}


void Texture::GenerateCubeMap(unsigned int width, unsigned int height, std::vector<unsigned char*> faces)
{
	this->textureType = GL_TEXTURE_CUBE_MAP;
	this->width = width;
	this->height = height;

	this->Bind();


	for (int i = 0; i < faces.size(); i++) {
		// create texture	
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, this->internal_Format, width, height, 0, this->image_Format, GL_UNSIGNED_BYTE, faces[i]);
	}

	// set texture wrap and filter modes
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, this->wrap_S);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, this->wrap_T);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, this->filter_Min);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, this->filter_Max);

	// unbind texture
	this->Unbind();
}

void Texture::Bind()
{
    glBindTexture(textureType, this->ID);
}

void Texture::Unbind()
{
    glBindTexture(textureType, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &this->ID);
}
