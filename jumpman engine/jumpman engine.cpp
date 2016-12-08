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
#include "JUMA_shapes.h"
int main(int argc, char* args[])
{
	JUMA_RenderES renderEssentials;
	renderEssentials=initJUMA(600,600, "fuak");
	initShapes(JUMA_SQUARE | JUMA_TRIANGLE);
	SDL_Delay(10000);
	return 1;
}

