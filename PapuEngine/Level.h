#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"

using namespace std;

const int TILE_WIDTH = 64;

class Level {
private:
	vector<string> _levelData;
	void parseLevel();
public:
	Level(const std::string& fileName);
	~Level();

	SpriteBacth _spriteBatch;
	glm::vec2 _playerPosition;
	std::vector<glm::vec2> _zombiesPosition;
	glm::vec2 getPlayerPosition() const { 
		return _playerPosition; 
	};

	const std::vector<std::string>& getLevelData() {
		return _levelData;
	}

	int getWidth() const {
		return _levelData[0].size();
	}

	int getHeight() const {
		return _levelData.size() - 1;
	}

	std::vector<glm::vec2> getZombiesPosition()const {
		return _zombiesPosition;
	};

	void draw();
};

