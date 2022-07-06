#include "Player.h"
#include <SDL\SDL.h>
#include <windows.h>
#include <iostream>
#include "ResourceManager.h"

using namespace std;


void Player::init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera, Weapon* weapon) {
	_speed = speed;
	_position = position;
	_inputManager = inputManager;
	_weapon = weapon;
	_camera = camera;
	color.set(255, 255, 255, 255);
	drawWeapon = false;
	soundWeapon = false;
	stunned = false;
	stunnedTime = 2000;
	spriteActual = "Textures/player_alien.png";

}
void Player::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, glm::vec2 player_position, bool _gameplay) {
	
	if (stunned && stunnedTime > 0)
	{
		stunnedTime -= 1;
		cout << "Player is stunned: " << stunnedTime << endl;
		drawWeapon = false;
		soundWeapon = false;
		return;
	}
	else
	{
		stunned = false;
		stunnedTime = 125;
	}
	collideWithZombies(zombies);

	if (_inputManager->isKeyDown(SDLK_UP) == false && _inputManager->isKeyDown(SDLK_DOWN) == false && _inputManager->isKeyDown(SDLK_LEFT) == false && _inputManager->isKeyDown(SDLK_RIGHT) == false)
	{
		drawWeapon = false;
	}
	else
	{
		//arma
		if(_gameplay){
			if (_inputManager->isKeyDown(SDLK_UP)) {
			_weapon->direccion = Direction::UP;
			drawWeapon = true;
		}
			if (_inputManager->isKeyDown(SDLK_DOWN)) {
			_weapon->direccion = Direction::DOWN;
			drawWeapon = true;
		}
			if (_inputManager->isKeyDown(SDLK_LEFT)) {
			_weapon->direccion = Direction::LEFT;
			drawWeapon = true;
		}
			if (_inputManager->isKeyDown(SDLK_RIGHT)) {
			_weapon->direccion = Direction::RIGHT;
			drawWeapon = true;
			}
		}
	}
	//movimiento
	if (_gameplay && !drawWeapon)
	{
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
		soundWeapon = false;
	}
	collideWithLevel(levelData);
}

void Player::collideWithZombies(std::vector<Zombie*>& zombies) {
	for each (Zombie * zombie in zombies)
	{
		if (collideWithAgent(zombie))
		{
			stunned = true;
			break;
		}
	}

}


Player::Player()
{
	drawWeapon = false;
}


Player::~Player()
{
}
