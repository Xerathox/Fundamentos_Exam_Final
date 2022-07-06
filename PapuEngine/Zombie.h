#pragma once
#include "Agent.h"

class Zombie :public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 position, int tipo);

	void update(const std::vector<std::string>& levelData,	
		std::vector<Zombie*>& zombies,
		glm::vec2 player_position
	);

	int _tipo_de_zombie;
	glm::vec2 _direction;
	bool collideWithPlayer(int pos_x, int pos_y, int height, int width);
	bool rectRect(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);
};

