#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vector>
class Music
{
private:
	std::vector<Mix_Chunk*> vMusic;


public:
	Music();
	~Music();

	void addSoundEffect(const char* path);
	void SDL2SoundEffect(const int which) const;

};
