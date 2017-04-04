#pragma once
//____________________REFERENCES___________________________
///Internet:
//Creating an SDL Rendering Context for opengl
	//https://wiki.libsdl.org/SDL_GL_CreateContext
//Creating an SDL Window
	//https://wiki.libsdl.org/SDL_CreateWindow
//Creating an SDL Renderer
	//https://wiki.libsdl.org/SDL_CreateRenderer
//Getting SDL errors
	//https://wiki.libsdl.org/SDL_GetError
//Initializing GLEW && GLEW debugging/versions
	//http://glew.sourceforge.net/basic.html

//_____________________DEFINES_____________________________
#define INITERR_SDL_WINDOW -1
#define INITERR_SDL_RENDERER -2
#define INITERR_SDL_OPENGL -3
#define INITERR_SDL_MULTIPLE -4
#define INITERR_GLEW -5
#define INITERR_UNDEFINED -999

//____________________INCLUDES_____________________________
#include <SDL2/SDL.h>

//____________________STRUCTURES___________________________
struct JUMA_RenderES {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_GLContext glcontext;
};

//___________________PROTOTYPES____________________________

JUMA_RenderES initJUMA(int width, int height, char* windowname);
int initSDL(SDL_Renderer *&renderer, SDL_Window *&window, SDL_GLContext *glcontext, int width, int height, char* windowname);
int initGLEW();
