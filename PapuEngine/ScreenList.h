#pragma once
#include <vector>
class Game;
class IGameScreen;

class ScreenList
{
public:
	ScreenList(Game* game);
	~ScreenList();
	IGameScreen* moveNext();
	IGameScreen* movePrevious();
	void setScreen(int nextScreen);
	void addScreen(IGameScreen* newScreen);
	void destroy();
	IGameScreen* getCurrent();
	int _currentIndex = -1;
protected:
	std::vector<IGameScreen*> _screens;
	Game* _game;
	
};

