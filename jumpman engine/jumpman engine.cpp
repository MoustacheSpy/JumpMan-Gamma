// jumpman engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//Opengl includes
#include <GL/glew.h>
//SDL includes
#include <SDL.h>
#include <SDL_opengl.h>
//JUMA includes
#include "JUMA_gameObject.h"
#include "JUMA_liftoff.h"
#include "JUMA_shapes.h"
#include "JUMA_shaders.h"
#include "JUMA_textures.h"
#include "JUMA_materials.h"
#include "JUMA_animatedTextures.h"


double test(float mousex, float mousey) {
	float deltaY = mousex - 10; //hardcoded y coordinate of the tip of the spaceship
	float deltaX = mousey - 0; //hardcoded x coordinate of the tip of the spaceship

	return  atan2(deltaY, deltaX) * 180 / 3.141;

}
int main(int argc, char* args[])
{
	double x=0.0, y=0.0, z=0.0, xr = 0.0, yr = 0.0, zr = 0.0;
	JUMA_RenderES renderEssentials;
	renderEssentials=initJUMA(600,600, "JUMPMAN_V1");
	JUMA_GO testObject(JUMA_RECTANGLE, 10.0f, "model");
	initShapes(JUMA_RECTANGLE );
	JUMA_Shader basic("./shaders/texture/texture.vs", "./shaders/texture/texture.frag");
	JUMA_Texture logo("./textures/jumpman.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material material;
	material.push_back(JUMA_materialFracture(&logo, JUMA_color(0.5, 0.5, 0.5, 1.0), "ourTexture", GL_TEXTURE10));
	material.push_back(JUMA_materialFracture(NULL, JUMA_color(0.2, 0, 0.7, 1.0), "mixCol", GL_TEXTURE1));
	while (1) {
		SDL_PollEvent(NULL);
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		glClearColor(0, 0, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		if (keystate[SDL_SCANCODE_S])
			xr += 0.01;
		if (keystate[SDL_SCANCODE_A])
			yr -= 0.01;
		if (keystate[SDL_SCANCODE_1])
			z += 0.01;
		if (keystate[SDL_SCANCODE_2])
			z -= 0.01;
		
		
		glm::mat4 model, view, proj;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		proj = glm::perspective(45.0f, (float)(600 / 600), 0.1f, 100.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//drawRectangle(basic, "model", x, y, z, xr, yr, 0.0f, 0.5f, 0.5f, 0.5f);
		drawRectangle3D(basic,material, JUMA_MakeCollection(model, view, proj, "model", "view", "projection"), x, y, z, xr, yr, 0.0, 4, 4, 4);
		drawTriangle3D(basic, JUMA_MakeCollection(model, view, proj, "model", "view", "projection"), x+0.9,y+0.1, z, xr, yr, 0.0f, 0.5f, 0.5f, 0.5f);
		SDL_GL_SwapWindow(renderEssentials.window);
		SDL_Delay(10);
	}
	return 1;
}