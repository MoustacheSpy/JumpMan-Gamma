#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <JUMA_textures.h>
#include <GL\glew.h>
class JUMA_Font {
private:
	SDL_Surface *sourceSurface;
	TTF_Font *font;
	int type;
	GLuint texture;
public:
	
	JUMA_Font() {};
	JUMA_Font(char *path, int size, SDL_Color color, char* text);
	JUMA_Texture makeTexture();
};