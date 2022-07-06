#include "Player.h"
#include <SDL\SDL.h>
#include <windows.h>
#include <iostream>
#include "ResourceManager.h"

using namespace std;

void Player::init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera) {
	_speed = speed;
	_position = position;
	_inputManager = inputManager;
	_camera = camera;
	color.set(255, 255, 255, 255);
	spriteActual = "Textures/player_alien.png";

}
void Player::update(const std::vector<std::string>& levelData, std::vector<Zombie*>& zombies, glm::vec2 player_position) {

	collideWithZombies(zombies);

	//movimiento
	if (_inputManager->isKeyDown(SDLK_UP)) {
		_position.y += _speed;
	}
	if (_inputManager->isKeyDown(SDLK_DOWN)) {
		_position.y -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_LEFT)) {	
		_position.x -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_RIGHT)) {
		_position.x += _speed;
	}
	collideWithLevel(levelData);
}

void Player::collideWithZombies(std::vector<Zombie*>& zombies) {
	for each (Zombie * zombie in zombies)
	{
		if (collideWithAgent(zombie))
		{	
			break;
		}
	}
}

Player::Player() {	
}
Player::~Player() {
}
