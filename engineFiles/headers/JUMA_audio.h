#pragma once
#include <SDL2/SDL_mixer.h>
#include <vector>
struct JUMA_chunk {
	Mix_Chunk *chunk;
	char name[100];
};

struct JUMA_music {
	Mix_Music *music;
	char name[100];
};

class JUMA_AudioChannel {
private:
	std::vector<JUMA_chunk> chunks;
	std::vector<JUMA_music> music;
public:
	void loadChunk(char *file, char *name);
	void loadMusic(char *file, char *name);
	void playChunk(char name[]);
	void playMusic(char name[]);
};
