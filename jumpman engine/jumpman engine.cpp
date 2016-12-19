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
	float x=0.0, y=0.0, z=0.0, xr = 0.0, yr = 0.0, zr = 0.0;
	JUMA_RenderES renderEssentials;
	renderEssentials=initJUMA(600,600, "JUMPMAN_V1");
	initShapes(JUMA_RECTANGLE );
	JUMA_Shader basic("./shaders/colorTest/colorTest.vs", "./shaders/colorTest/colorTest.frag");
	while (1) {
		SDL_PollEvent(NULL);
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		if (keystate[SDL_SCANCODE_UP])
			y += 0.01;
		if (keystate[SDL_SCANCODE_LEFT])
			x -= 0.01;
		if (keystate[SDL_SCANCODE_RIGHT])
			x += 0.01;
		if (keystate[SDL_SCANCODE_DOWN])
			y -= 0.01;
		if (keystate[SDL_SCANCODE_W])
			yr += 0.01;
		if (keystate[SDL_SCANCODE_D])
			xr -= 0.01;
		if (keystate[SDL_SCANCODE_S])
			xr += 0.01;
		if (keystate[SDL_SCANCODE_A])
			yr -= 0.01;
		glm::mat4 model, view, proj;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		proj = glm::perspective(45.0f, (float)(600 / 600), 0.1f, 100.0f);
		//drawRectangle(basic, "model", x, y, z, xr, yr, 0.0f, 0.5f, 0.5f, 0.5f);
		drawRectangle3D(basic, JUMA_MakeCollection(model, view, proj, "model", "view", "projection"), x, y, z, xr, yr, 0.0f, 0.5f, 0.5f, 0.5f);
		SDL_GL_SwapWindow(renderEssentials.window);
		SDL_Delay(10);
	}
	return 1;
}

