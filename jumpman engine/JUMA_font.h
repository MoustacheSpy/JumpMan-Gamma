#pragma once
#include <SDL.h>
#include "SDL_ttf.h"
#include <GL\glew.h>
class JUMA_Font {
private:
	SDL_Surface *sourceSurface;
	TTF_Font *font;
public:
	GLuint texture;
	JUMA_Font() {};
	JUMA_Font(char *path, int size, SDL_Color color, char* text);
	
};