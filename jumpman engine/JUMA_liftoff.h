#pragma once
//____________________REFERENCES___________________________
///Internet:
//Creating an SDL Rendering Context for opengl
	//https://wiki.libsdl.org/SDL_GL_CreateContext
//Creating an SDL Window
	//https://wiki.libsdl.org/SDL_CreateWindow
//Creating an SDL Renderer
	//https://wiki.libsdl.org/SDL_CreateRenderer
//Initializing GLEW && GLEW versions
	//http://glew.sourceforge.net/basic.html

//_____________________DEFINES_____________________________
#define INITERR_SDL -1
#define INITERR_GLEW -2
#define INITERR_UNDEFINED -999

//____________________INCLUDES_____________________________
#include <SDL.h>
struct JUMA_RenderES {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_GLContext glcontext;
};

int initJUMA(JUMA_RenderES *RenderEssentials);
int initSDL(SDL_Renderer *&renderer, SDL_Window *&window,SDL_GLContext *glcontext);
int initGLEW();