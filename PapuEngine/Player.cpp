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
void Player::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, glm::vec2 player_position) {

	collideWithZombies(zombies);

	//movimiento
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += _speed;
	}
	if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_a)) {	
		_position.x -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += _speed;
	}
	collideWithLevel(levelData);
}

void Player::collideWithZombies(std::vector<Zombie*>& zombies) {
	for each (Zombie * zombie in zombies)
	{
		if (collideWithAgent(zombie))
		{
			cout << "Se esta chocando con zombies" << endl;			
			break;
		}
	}
}

Player::Player() {	
}
Player::~Player() {
}
