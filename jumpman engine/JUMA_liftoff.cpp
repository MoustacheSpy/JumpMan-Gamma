#include "stdafx.h"
#include "JUMA_liftoff.h"
#include <GL/glew.h>
#include <string.h>

int initSDL(SDL_Renderer *&renderer, SDL_Window *&window, SDL_GLContext *glcontext, int width, int height, char* windowname) {
	bool windowNull = false, rendererNull = false, glNull = false;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(windowname, 10, 100, width, height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	*glcontext = SDL_GL_CreateContext(window);
	if (window == NULL) {
		printf("INIT ERROR: %s (windowIsNull)\n", SDL_GetError());
		windowNull = true;
	}
	if (renderer == NULL) {
		printf("INIT ERROR: %s (rendererIsNull)\n", SDL_GetError());
		rendererNull = true;
	}
	if (glcontext == NULL) {
		printf("INIT ERROR: %s (glcontextisNull)\n", SDL_GetError());
		glNull = true;
	}
	if (rendererNull) {
		if (windowNull || glNull)
			return INITERR_SDL_MULTIPLE;
		return INITERR_SDL_RENDERER;
	}
	else {
		if (windowNull) {
			if (rendererNull || glNull)
				return INITERR_SDL_MULTIPLE;
			return INITERR_SDL_WINDOW;
		}
		else {
			if (glNull) {
				if (windowNull || rendererNull)
					return INITERR_SDL_MULTIPLE;
				return INITERR_SDL_OPENGL;
			}
		}
	}
	return 1;
}
int initGLEW() {
	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf( "GLEWINIT ERROR: %s\n", glewGetErrorString(err));
		return INITERR_GLEW;
	}
	else printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	return 1;
}
JUMA_RenderES initJUMA(int width, int height, char* windowname) {
	JUMA_RenderES RenderEssentials;
	initSDL(RenderEssentials.renderer, RenderEssentials.window, &RenderEssentials.glcontext,width,height, windowname);
	initGLEW();
	return RenderEssentials;
}
