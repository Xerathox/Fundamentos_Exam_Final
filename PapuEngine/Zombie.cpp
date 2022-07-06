#include "Zombie.h"
#include "Human.h"


Zombie::Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position) {
	_speed = speed;
	_position = position;
	color.set(255, 255, 255, 255);
}

void Zombie::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	glm::vec2 player_position,
	bool _gameplay//quitar esto, que ya no lo reciba, hasta el Agent
	
) {
	collideWithLevel(levelData);
	Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		glm::vec2 direction = glm::normalize(
			closeHuman->getPosition() - _position
		);
		_position += direction * _speed;
	}
	//else
	//{
	//	glm::vec2 direction = glm::normalize(
	//		player_position - _position
	//	);
	//	_position += direction * _speed;
	//}
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans)
{
	Human* closesHuman = nullptr;
	float smallDistance = 8888888888.0f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - _position;
		float distance = glm::length(dist);
		if (distance < smallDistance) {
			smallDistance = distance;
			closesHuman = humans[i];
		}
	}
	return closesHuman;
}

bool Zombie::collideWithWeapon(int pos_x, int pos_y, int height, int width) {

	return rectRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH, pos_x, pos_y, height, width);
}

bool Zombie::rectRect(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h) {

	// are the sides of one rectangle touching the other?

	if (r1x + r1w >= r2x &&    // r1 right edge past r2 left
		r1x <= r2x + r2w &&    // r1 left edge past r2 right
		r1y + r1h >= r2y &&    // r1 top edge past r2 bottom
		r1y <= r2y + r2h) {    // r1 bottom edge past r2 top
		return true;
	}
	return false;
}

Zombie::~Zombie()
{
}
