#include "resourceManager.h"

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;


std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ResourceManager::Clear()
{
	Shaders.clear();
	Textures.clear();
}



Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vShaderFile);
	std::string fragmentCode = get_file_contents(fShaderFile);

	Shader shader;
	shader.Compile(vertexCode.c_str(), fragmentCode.c_str());
	return shader;
}


Texture ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	if (data == NULL) {
		std::cout << "FAILED LOADING IMAGE " << file << '\n';
	}


	Texture texture;
	if (alpha) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format    = GL_RGBA;
	}
	texture.Generate(width, height, data);

	stbi_image_free(data);

    return texture;
}

