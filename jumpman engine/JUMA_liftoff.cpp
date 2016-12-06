#include "stdafx.h"
#include "JUMA_liftoff.h"
#include <GL/glew.h>
int initSDL(SDL_Renderer *&renderer, SDL_Window *&window, SDL_GLContext *glcontext,char *windowTitle,int width,int height) {
	window = SDL_CreateWindow(windowTitle, 10, 10, width, height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
int initGLEW() {
	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf( "GLEWINIT ERROR: %s\n", glewGetErrorString(err));
	}
}
int initJUMA(JUMA_RenderES *RenderEssentials);
