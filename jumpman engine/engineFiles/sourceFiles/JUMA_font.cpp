#include "stdafx.h"
#include <JUMA_font.h>
JUMA_Font::JUMA_Font(char *path, int size, SDL_Color color, char* text, char *uniform) {
	TTF_Init();
	font = TTF_OpenFont(path, size);
	if (font == NULL) {
		printf("error loading font.");
	}
	sourceSurface = TTF_RenderText_Solid(font, text, color);
	SDL_SaveBMP(sourceSurface, "test.bmp");
	if (font == NULL)
		printf("\nFATAL ERROR LOADING TTF FILE");
	if (sourceSurface == NULL)
		printf("\nFATAL ERROR ASSIGNING SURFACE IN FONT GENERATION");
	//./fonts/PlayfairDisplay-Regular.ttf
	int colors = sourceSurface->format->BytesPerPixel;
	if (colors == 4) {   // alpha
		if (sourceSurface->format->Rmask == 0x000000ff)
			type = GL_RGBA;
		else
			type = GL_BGRA;
	}
	else {             // no alpha
		if (sourceSurface->format->Rmask == 0x000000ff)
			type = GL_RGB;
		else
			type = GL_BGR;
	}

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, type, sourceSurface->w, sourceSurface->h, 0, type, GL_UNSIGNED_BYTE, sourceSurface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	JUMA_materialFracture fract;
	fract.JUMA_materialFractureGluint(&Texture, JUMA_color(0.5, 0.5, 0.5, 1.0), uniform, GL_TEXTURE0);
	mat.push_back(fract);
	TTF_CloseFont(font);

};

