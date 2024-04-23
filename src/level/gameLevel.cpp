//#include "gameLevel.h"
//#include "resourceManager.h"
//
//
//void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
//{
//	this->Bricks.clear();
//	unsigned int tileCode = 0;
///*
//	A number of 0: no brick, an empty space within the level.
//	A number of 1: a solid brick, a brick that cannot be destroyed.
//	A number higher than 1: a destroyable brick; each subsequent number only differs in color
//*/
//
//	std::vector<std::vector<unsigned int>> tileData;
//
//	std::string curLine;
//	std::ifstream in(file);
//	if (!in) {
//		std::cout << "ERROR::FAILED_TO_READ_LEVEL_DATA " << file << '\n';
//	}
//	while (std::getline(in, curLine))
//	{
//		std::istringstream sstream(curLine);
//		std::vector<unsigned int> row;
//		unsigned int tileCode;
//		while (sstream >> tileCode)
//		{
//			row.push_back(tileCode);
//		}
//		tileData.push_back(row);
//	}
//	if (tileData.size() > 0)
//		this->init(tileData, levelWidth, levelHeight);
//}
//
//void GameLevel::Draw(CubeRenderer& renderer)
//{
//	for (GameObject brick : this->Bricks) {
//		brick.Draw(renderer);
//	}
//}
//
//bool GameLevel::IsCompleted()
//{
//	return false;
//}
//
//void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
//{
//	unsigned int height = tileData.size();
//	unsigned int width = tileData[0].size();
//	float unit_width = levelWidth / (float)width;
//	float unit_height = levelHeight / height;
//
//	for (unsigned int y = 0; y < height; y++) {
//		for (unsigned int x = 0; x < width; x++) {
//			if (tileData[y][x] == 1) { // solid block
//				glm::vec2 pos(unit_width * x, unit_height * y);
//				glm::vec2 size(unit_width, unit_height);
//				glm::vec3 color(0.9f, 0.8f, 0.85f);
//
//				GameObject obj(pos, size,
//					ResourceManager::GetTexture("block_solid"),
//					color);
//
//				obj.IsSolid = true;
//				this->Bricks.push_back(obj);
//			}
//			else if (tileData[y][x] > 1) { // colored block
//				glm::vec2 pos(unit_width * x, unit_height * y);
//				glm::vec2 size(unit_width, unit_height);
//				glm::vec3 color(1.0f);
//
//				if (tileData[y][x] == 2)
//					color = glm::vec3(0.2f, 0.6f, 1.0f);
//				else if (tileData[y][x] == 3)
//					color = glm::vec3(0.0f, 0.7f, 0.0f);
//				else if (tileData[y][x] == 4)
//					color = glm::vec3(0.8f, 0.8f, 0.4f);
//				else if (tileData[y][x] == 5)
//					color = glm::vec3(1.0f, 0.5f, 0.0f);
//
//				GameObject obj(pos, size,
//					ResourceManager::GetTexture("block"), color);
//
//				this->Bricks.push_back(obj);
//			}
//		}
//	}
//}
