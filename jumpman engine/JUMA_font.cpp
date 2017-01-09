#include "stdafx.h"
#include "JUMA_font.h"
JUMA_Font::JUMA_Font(char *path, int size, SDL_Color color, char* text) {
	TTF_Init();
	font = TTF_OpenFont(path, size);
	sourceSurface = TTF_RenderText_Solid(font, text, color);
	//./fonts/PlayfairDisplay-Regular.ttf
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int Mode = GL_RGB;

	if (sourceSurface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, sourceSurface->w, sourceSurface->h, 0, Mode, GL_UNSIGNED_BYTE, sourceSurface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
};