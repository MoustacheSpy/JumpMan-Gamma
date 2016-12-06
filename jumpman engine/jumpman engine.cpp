// jumpman engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//Opengl includes
#include <GL/glew.h>
//SDL includes
#include <SDL.h>
#include <SDL_opengl.h>
//JUMA includes
#include "JUMA_liftoff.h"
int main(int argc, char* args[])
{
	JUMA_RenderES renderEssentials;
	renderEssentials=initJUMA(600,600, "fuak");
	SDL_Delay(1000);
	return 1;
}

