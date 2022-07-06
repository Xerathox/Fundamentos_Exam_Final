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

	//contador 
	start = time(0);
	//jugador
	_player = new Player();
	//_currenLevel = 0;
	_player->init(3.5f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager, &_camera);	
	//_humans.push_back(_player);
	_spriteBatch.init();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(1, _levels[_currenLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randPosY(1, _levels[_currenLevel]->getHeight() - 2);

	cout << "Pos x" << _levels[_currenLevel]->getWidth() << endl;
	cout << "Pos y" << _levels[_currenLevel]->getHeight() << endl;

	//TODO creacion de humanos
	for (int i = 0; i < 50; i++)
	{
		_zombies.push_back(new Zombie());
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH);		
		_zombies.back()->init(1.3f, pos, (rand() % 3) + 1);
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
}

void GamePlayScreen::onEntry() {
	_program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
	spriteFont = new SpriteFont("Fonts/1_Minecraft-Regular.otf", 40);
	_background = new Background("Textures/Fondos/game.png");
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

	_background->draw(_spriteBatch, glm::vec4(0, 0, _levels[_currenLevel]->getWidth() * 64.0f, _levels[_currenLevel]->getHeight() * 65.0f));
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	_spriteBatch.begin();

	_player->draw(_spriteBatch, _player->spriteActual);
	_levels[_currenLevel]->draw();

	for (size_t i = 0; i < _zombies.size(); i++)
	{
		switch (_zombies[i]->_tipo_de_zombie) 
		{
		case 1:
			_zombies[i]->draw(_spriteBatch, "Textures/amarillo.png");
			break;
		case 2:
			_zombies[i]->draw(_spriteBatch, "Textures/rojo.png");
			break;
		case 3:
			_zombies[i]->draw(_spriteBatch, "Textures/verde.png");
			break;
		default:
			break;
		}

	}
	//background->draw(_spriteBatch);

	int seconds_since_start = difftime(time(0), start);

	//contador de tiempo
	char buffer[256];
	sprintf_s(buffer, "Tiempo: %d", seconds_since_start);
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(_player->getPosition().x - 875, _player->getPosition().y + 500), glm::vec2(2), 0.0f, color);

	//contador de Puntaje 
	//char buffer[256];
	sprintf_s(buffer, "Puntaje: %d", puntaje);
	//Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(_player->getPosition().x + 400, _player->getPosition().y + 500), glm::vec2(2), 0.0f, color);

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
	//TODO DERROTA
	/*if (_humans.size() <= 0) {
		char buffer[256];
		sprintf_s(buffer, "Perdiste");
		Color color;
		color.r = 255;
		color.g = 0;
		color.b = 0;
		color.a = 255;
		spriteFont->draw(_spriteBatch, buffer, glm::vec2(_player->getPosition().x - 125, _player->getPosition().y + 250), glm::vec2(2), 0.0f, color);
		_gamePlay = false;

	}*/
	 
	//boton para resetear juego
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

	
}

void GamePlayScreen::updateAgents() {
	//movimimento humanos
	_player->update(_levels[_currenLevel]->getLevelData(), _zombies, glm::vec2());

	//movimientos zombies
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currenLevel]->getLevelData(), _zombies, _player->getPosition());

		//destruccion de zombies cuando interactuan con humanos
		if (_zombies[i]->collideWithPlayer(_player->getPosition().x, _player->getPosition().y, AGENT_WIDTH, AGENT_WIDTH))
		{
			if (_inputManager.isKeyDown(SDLK_q))
			{
				updatePuntaje(1,_zombies[i]->_tipo_de_zombie);
				delete _zombies[i];
				_zombies[i] = _zombies.back();
				_zombies.pop_back();
			}
			else if (_inputManager.isKeyDown(SDLK_w))
			{
				updatePuntaje(2, _zombies[i]->_tipo_de_zombie);
				delete _zombies[i];
				_zombies[i] = _zombies.back();
				_zombies.pop_back();
			}
			else if (_inputManager.isKeyDown(SDLK_e))
			{
				updatePuntaje(3, _zombies[i]->_tipo_de_zombie);
				delete _zombies[i];
				_zombies[i] = _zombies.back();
				_zombies.pop_back();
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
		if (_inputManager.isKeyDown(SDLK_z)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyDown(SDLK_x)) {
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

void GamePlayScreen::updatePuntaje(int tecla, int tipo) {
	switch (tecla)
	{
	case 1:
		switch (tipo)
		{
		case 1:
			cout << "Tecla q y zombie amarillo" << endl;
			puntaje += 10;
			break;
		case 2:
			cout << "Tecla q y zombie rojo" << endl;
			puntaje -= 10;
			break;
		case 3:
			cout << "Tecla q y zombie verde" << endl;
			puntaje -= 20;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (tipo)
		{
		case 1:
			cout << "Tecla w y zombie amarillo" << endl;
			puntaje += 15;
			break;
		case 2:
			cout << "Tecla w y zombie rojo" << endl;
			puntaje += 20;
			break;
		case 3:
			cout << "Tecla w y zombie verde" << endl;
			puntaje -= 15;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (tipo)
		{
		case 1:
			cout << "Tecla e y zombie amarillo" << endl;
			puntaje /= 2;
			break;
		case 2:
			cout << "Tecla e y zombie rojo" << endl;
			puntaje -= 5;
			break;
		case 3:
			cout << "Tecla e y zombie verde" << endl;
			puntaje *= 2;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
