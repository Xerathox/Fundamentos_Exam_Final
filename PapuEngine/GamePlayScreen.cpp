#include "GamePlayScreen.h"
#include "Game.h"

#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"
#include "ScreenIndices.h"
#include <random>
#include <ctime>

using namespace std;

GamePlayScreen::GamePlayScreen(Window* window) :
	_window(window){
	_music.addSoundEffect("Music/Kamehameha.wav");
	_music.addSoundEffect("Music/Hell_on_Earth.wav");
	_music.addSoundEffect("Music/BFG Division.wav");	
	_music.addSoundEffect("Music/Rip_&_Tear.wav");
	_music.addSoundEffect("Music/TOTTFIY.wav");
	_btnReplay = new Button(-100000, -100000, 170, 80, "Textures/btn_retry.png");
	//_background = new Background("Textures/Fondos/background.png");
	_screenIndex = SCREEN_INDEX_GAMEPLAY;
	_currenLevel = 0;
	_gamePlay = true;
	_gameRetry = false;
}

GamePlayScreen::~GamePlayScreen()
{
	_btnReplay = nullptr;
}

void GamePlayScreen::build() {
	_levels.push_back(new Level("Levels/level1.txt"));
	_levels.push_back(new Level("Levels/level2.txt"));
	_levels.push_back(new Level("Levels/level3.txt"));
	_levels.push_back(new Level("Levels/level4.txt"));

	_music.SDL2SoundEffect(_currenLevel+1);

	_player = new Player();
	_weapon = new Weapon();
	//_currenLevel = 0;
	_player->init(3.5f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager, &_camera, _weapon);	
	//_humans.push_back(_player);
	_spriteBatch.init();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(1, _levels[_currenLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randPosY(1, _levels[_currenLevel]->getHeight() - 2);

	cout << "Pos x" << _levels[_currenLevel]->getWidth() << endl;
	cout << "Pos y" << _levels[_currenLevel]->getHeight() << endl;

	//creacion de humanos
	for (int i = 0; i < _levels[_currenLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(1.0f, pos);
	}

	//creacion de zombies
	const std::vector<glm::vec2>& zombiePosition =
		_levels[_currenLevel]->getZombiesPosition();

	for (size_t i = 0; i < zombiePosition.size(); i++)
	{
		_zombies.push_back(new Zombie());
		_zombies.back()->init(1.3f, zombiePosition[i]);
	}
	
}
void GamePlayScreen::destroy() {

}
void GamePlayScreen::onExit() {
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		delete _zombies[i];
		_zombies[i] = _zombies.back();
		_zombies.pop_back();
	}
	for (size_t i = 0; i < _humans.size(); i++)
	{
		delete _humans[i];
		_humans[i] = _humans.back();
		_humans.pop_back();
	}
}

void GamePlayScreen::onEntry() {
	_program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
	spriteFont = new SpriteFont("Fonts/1_Minecraft-Regular.otf", 40);

	_camera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
}
void GamePlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	
	/*GLuint timeLocation =
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);*/

	GLuint pLocation = _program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBatch.begin();
	_player->draw(_spriteBatch, _player->spriteActual);
	_levels[_currenLevel]->draw();


	if (_player->drawWeapon)
	{
		_weapon->draw(_spriteBatch, _player->getPosition().x, _player->getPosition().y);
	}
	else
	{
		_weapon->reset();
	}
	for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_spriteBatch, "Textures/human.png");
	}

	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_spriteBatch, "Textures/zombie.png");
	}
	//background->draw(_spriteBatch);
	
	//contador de zombies
	char buffer[256];
	sprintf_s(buffer, "Zombies: %d", _zombies.size());
	Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(_player->getPosition().x-875, _player->getPosition().y + 500), glm::vec2(2), 0.0f, color);

	//contador de humanos
	//char buffer[256];
	sprintf_s(buffer, "Humanos: %d", _humans.size());
	//Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(_player->getPosition().x - 875, _player->getPosition().y + 400), glm::vec2(2), 0.0f, color);

	//contador de nivel
	sprintf_s(buffer, "Nivel Actual: %d", _currenLevel + 1);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(_player->getPosition().x - 875, _player->getPosition().y + 300), glm::vec2(2), 0.0f, color);


	//VICTORIA
	if (_currenLevel == 3 && _zombies.size() <= 0) {
		char buffer[256];
		sprintf_s(buffer, "Ganaste");
		Color color;
		color.r = 0;
		color.g = 255;
		color.b = 0;
		color.a = 255;
		spriteFont->draw(_spriteBatch, buffer, glm::vec2(_player->getPosition().x - 125, _player->getPosition().y + 250), glm::vec2(2), 0.0f, color);
		_gamePlay = false;
		if (!_gamePlay && _currenLevel == 3) {
			_btnReplay->draw(_spriteBatch, glm::vec2(_player->getPosition().x-50, _player->getPosition().y + 100));
			//spriteFont->draw(_btnReplay->draw(_spriteBatch), glm::vec2(_player->getPosition().x - 125, _player->getPosition().y + 250), glm::vec2(2), 0.0f, color);
		}
	}
	//DERROTA
	if (_humans.size() <= 0) {
		char buffer[256];
		sprintf_s(buffer, "Perdiste");
		Color color;
		color.r = 255;
		color.g = 0;
		color.b = 0;
		color.a = 255;
		spriteFont->draw(_spriteBatch, buffer, glm::vec2(_player->getPosition().x - 125, _player->getPosition().y + 250), glm::vec2(2), 0.0f, color);
		_gamePlay = false;

	}
	// 
	if (!_gamePlay) {
		_btnReplay->draw(_spriteBatch, glm::vec2(_player->getPosition().x-50, _player->getPosition().y + 100));
		//spriteFont->draw(_btnReplay->draw(_spriteBatch), glm::vec2(_player->getPosition().x - 125, _player->getPosition().y + 250), glm::vec2(2), 0.0f, color);
	}


	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}
void GamePlayScreen::update() {
	checkInput();
	draw();
	_camera.update();
	updateAgents();
	_inputManager.update();
	_camera.setPosition(_player->getPosition());

	//logica de niveles
	if (_zombies.size() <= 0 && _currenLevel+1 < 4) {
		_currenLevel++;
		onExit();
		build();		
	}
	manageMusic();
	
}

void GamePlayScreen::manageMusic()
{
	if (_player->drawWeapon)
	{
		if (!_player->soundWeapon)
		{
			cout << "Playing weapon sound." << endl;
			_music.SDL2SoundEffect(0);
			_player->soundWeapon = true;
		}
	}
}

void GamePlayScreen::updateAgents() {

	_player->update(_levels[_currenLevel]->getLevelData(), _humans, _zombies, glm::vec2(),_gamePlay);
	for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currenLevel]->getLevelData(), _humans, _zombies, glm::vec2(),_gamePlay);
	}

	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currenLevel]->getLevelData(), _humans, _zombies, _player->getPosition(),_gamePlay);

		if (_zombies[i]->collideWithWeapon(_weapon->pos_x, _weapon->pos_y, _weapon->height, _weapon->width))
		{
			delete _zombies[i];
			_zombies[i] = _zombies.back();
			_zombies.pop_back();
		}
		else
		{
			for (size_t j = 0; j < _humans.size(); j++)
			{
				if (_zombies[i]->collideWithAgent(_humans[j])) {
					_zombies.push_back(new Zombie());
					_zombies.back()->init(1.3f, _humans[j]->getPosition());
					delete _humans[j];
					_humans[j] = _humans.back();
					_humans.pop_back();
				}
			}
		}
	}
}

void GamePlayScreen::checkInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			//_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case  SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case  SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);
			break;
		}
		if (_inputManager.isKeyDown(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyDown(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			//presione click;
			glm::vec2 mouseCoords = _camera.convertScreenToWorl(_inputManager.getMouseCoords());
			if (_btnReplay->click(mouseCoords)) {
				onExit();
				_currenLevel = 0;
				build();
				_gamePlay = true;
			}
		}
		
	}
}
int GamePlayScreen::getNextScreen() const {
	return -1;
};
int GamePlayScreen::getPreviousScreen() const {
	return -1;
}
