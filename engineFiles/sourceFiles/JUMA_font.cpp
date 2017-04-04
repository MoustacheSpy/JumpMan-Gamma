
#include <JUMA_font.h>
JUMA_Font::JUMA_Font(char *path, int size, SDL_Color color, char* text, char *uniform) {
	TTF_Init();
	font = TTF_OpenFont(path, size);
//	SDL_SetSurfaceBlendMode(sourceSurface, SDL_BLENDMODE_BLEND);

	sourceSurface = TTF_RenderText_Blended(font, text, color);

	printf("%d %d %d %d", color.r, color.g, color.b, color.a);
};

int JUMA_Font::changeText(const char* text, SDL_Color color) {
	sourceSurface = TTF_RenderText_Blended(font, text, color);
	return 1;
}
