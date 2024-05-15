#pragma once
#include <vector>



class GameLevel
{
public:
	std::vector<Cube> cubes;

	GameLevel() { }
	void Load(const char* file);
	void Draw();
	bool IsCompleted();

private:
	void init(std::vector<std::vector<unsigned int>> tileData);
};

