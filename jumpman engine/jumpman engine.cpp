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
#include "JUMA_shaders.h"
int main(int argc, char* args[])
{
	JUMA_RenderES renderEssentials;
	renderEssentials=initJUMA(600,600, "fuak");
	initShapes(JUMA_RECTANGLE | JUMA_TRIANGLE);
	JUMA_Shader basic("C:/Users/MoustacheSpy/Documents/Visual Studio 2015/Projects/jumpman engine/jumpman engine/shaders/colorTest/colorTest.vs", "C:/Users/MoustacheSpy/Documents/Visual Studio 2015/Projects/jumpman engine/jumpman engine/shaders/colorTest/colorTest.frag");
	drawRectangle(basic, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SDL_GL_SwapWindow(renderEssentials.window);
	SDL_Delay(10000);
	return 1;
}

