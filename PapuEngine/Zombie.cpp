#include "Zombie.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

Zombie::Zombie(){
}

void Zombie::init(float speed, glm::vec2 position) {
	_speed = speed;
	color.set(255, 255, 255, 255);
	_position = position;
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);

	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (_direction.length() == 0) {
		_direction = glm::vec2(1.0f, 1.0f);
	}
	_direction = glm::vec2(_direction);
}

void Zombie::update(const std::vector<std::string>& levelData, std::vector<Zombie*>& zombies, glm::vec2 player_position) {
	_position += _direction * _speed;
	if (collideWithLevel(levelData)) {
		static std::mt19937 randomEngine(time(nullptr));
		static std::uniform_real_distribution<float>randRotate(-40.0f, 40.0f);
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
}

bool Zombie::collideWithPlayer(int pos_x, int pos_y, int height, int width) {

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
