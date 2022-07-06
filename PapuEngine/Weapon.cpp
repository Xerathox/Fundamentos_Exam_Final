#include "Weapon.h"
//#include "MainGame.h"
#include "ResourceManager.h"
#include <iostream>

Weapon::Weapon() {
	default_HEIGHT = 60.0f;
	default_WIDTH = 180.0f;
	pos_x = .0f;
	pos_y = .0f;
	direccion = Direction::RIGHT;
}

Weapon::~Weapon()
{
}

void Weapon::reset() {
	default_HEIGHT = 60.0f;
	default_WIDTH = 180.0f;
	pos_x = .0f;
	pos_y = .0f;
	direccion = Direction::RIGHT;
}

void Weapon::draw(SpriteBacth& spritebatch, int x, int y) {
	height = get_default_HEIGHT();
	width = get_default_WIDTH();
	pos_x = get_pos_x(x, width);
	pos_y = get_pos_y(y, height);
	Color color{};
	color.set(255, 255, 255, 255);

	static int textureID = ResourceManager::getTexture("Textures/weapon.png").id;
	static int textureID2 = ResourceManager::getTexture("Textures/weapon2.png").id;
	static int textureID3 = ResourceManager::getTexture("Textures/weapon3.png").id;
	static int textureID4 = ResourceManager::getTexture("Textures/weapon4.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(pos_x, pos_y, height, width);


	switch (direccion)
	{
	case Direction::UP:
		spritebatch.draw(destRect, uvRect, textureID4, 0.0f, color);
		break;
	case Direction::DOWN:
		spritebatch.draw(destRect, uvRect, textureID2, 0.0f, color);
		break;
	case Direction::LEFT:
		spritebatch.draw(destRect, uvRect, textureID3, 0.0f, color);
		break;
	case Direction::RIGHT:
		spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
		break;
	default:
		break;
	}
}

int Weapon::get_default_HEIGHT() {
	if (direccion == Direction::UP || direccion == Direction::DOWN)
	{
		return default_HEIGHT;
	}
	return default_WIDTH;
}

int Weapon::get_default_WIDTH() {
	if (direccion == Direction::UP || direccion == Direction::DOWN)
	{
		return default_WIDTH;
	}
	return default_HEIGHT;
}

int Weapon::get_pos_x(int x, int width)
{
	switch (direccion)
	{
	case Direction::UP:
		return x;
		break;
	case Direction::DOWN:
		return x;
		break;
	case Direction::LEFT:
		return x - width - (2 * AGENT_WIDTH);
		break;
	case Direction::RIGHT:
		return x + width;
		break;
	default:
		break;
	}
}

int Weapon::get_pos_y(int y, int height)
{
	switch (direccion)
	{
	case Direction::UP:
		return y + height;
		break;
	case Direction::DOWN:
		return y - height - (2 * AGENT_WIDTH);
		break;
	case Direction::LEFT:
		return y;
		break;
	case Direction::RIGHT:
		return y;
		break;
	default:
		break;
	}
}
