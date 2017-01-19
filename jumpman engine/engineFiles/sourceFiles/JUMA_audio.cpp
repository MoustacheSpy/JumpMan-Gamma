#include "stdafx.h"
#include <JUMA_audio.h>

void JUMA_AudioChannel::loadChunk(char *file, char *name) {
	JUMA_chunk temp;
	temp.chunk = Mix_LoadWAV(file);
	strcpy(temp.name, name);
	chunks.push_back(temp);
}
void JUMA_AudioChannel::loadMusic(char *file, char *name) {
	JUMA_music temp;
	temp.music = Mix_LoadMUS(file);
	strcpy(temp.name, name);
	music.push_back(temp);
}
void JUMA_AudioChannel::playChunk(char name[]) {
	int i = 0;
	for ( i = 0; i < chunks.size() && strcmp(chunks.at(i).name, name) != 0; i++);
	if (i != chunks.size()) {
		if (Mix_PlayChannel(-1, chunks.at(i).chunk, 0) == -1)
			printf("couldnt play chunk");
	}
	else printf("chunk not found");

}
void JUMA_AudioChannel::playMusic(char name[]) {
	int i = 0;
	for (i = 0; i < music.size() && strcmp(music.at(i).name, name) != 0; i++);
	if (i != music.size()) {
		if (Mix_PlayMusic(music.at(i).music, -1) == -1)
			printf("couldnt play music");
	}
	else printf("music not found");

}