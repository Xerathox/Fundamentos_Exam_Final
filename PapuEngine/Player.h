#pragma once
#include "Human.h"
#include "InputManager.h"
#include <vector>
#include "Camera2D.h"
#include "Music.h"
#include "Zombie.h"
#include "Weapon.h"

class Zombie;
class Human;

class Player: public Human
{
private:
	InputManager* _inputManager;
	//int _currentGun;
	Camera2D* _camera;

public:
	std::string spriteActual;
	std::string spriteDer;
	std::string spriteIzq;
	std::string spriteArr;
	std::string spriteAba;
	Weapon* _weapon;
	bool drawWeapon;
	bool soundWeapon;
	bool stunned;
	float stunnedTime;
	Player();
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera, Weapon* weapon);
	void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, glm::vec2 player_position, bool _gameplay);
	void collideWithZombies(std::vector<Zombie*>& zombies);
};

