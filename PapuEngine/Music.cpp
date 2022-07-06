#include "Music.h"

Music::Music()
{
	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;


	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No se pudo: ", Mix_GetError());
		exit(-1);
	}
}

Music::~Music()
{
	SDL_Quit();
}

void Music::addSoundEffect(const char* path)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(path);
	if (tmpChunk != nullptr)
	{
		vMusic.push_back(tmpChunk);
		//-> comentario imprimir el numero de canciones
	}
	else
		SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Sound Not Found %s", Mix_GetError());
}

void Music::SDL2SoundEffect(int which) const
{
	Mix_PlayChannel(-1, vMusic[which], 0);
}

