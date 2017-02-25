// jumpman engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//Opengl includes
#include <GL/glew.h>
//SDL includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <math.h>
#include <ctime>
//JUMA includes
#include "./engineFiles/headers/JUMA_gameObject.h"
#include "./engineFiles/headers/JUMA_liftoff.h"
#include "./engineFiles/headers/JUMA_shapes.h"
#include "./engineFiles/headers/JUMA_shaders.h"
#include "./engineFiles/headers/JUMA_textures.h"
#include "./engineFiles/headers/JUMA_materials.h"
#include "./engineFiles/headers/JUMA_animatedTextures.h"
#include "./engineFiles/headers/JUMA_font.h"
#include "./engineFiles/headers/JUMA_audio.h"
void drawLinesTest(std::vector<GLfloat> lines) {
	glLineWidth(25);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	srand(time(NULL));
	for(int i=0;i<lines.size();i++)
		glVertex3f(lines.at(i),rand(), 0.0);
	glEnd();

}


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
	
	initShapes(JUMA_RECTANGLE );
	JUMA_Shader basic("./shaders/texture/texture.vs", "./shaders/texture/texture.frag");
	JUMA_Texture logo("./textures/Fat_Spy.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material material;
	//JUMA_Font font("./fonts/PlayfairDisplay-Regular.ttf", 14, black, "test");
	material.push_back(JUMA_materialFracture(&logo, JUMA_color(0.5, 0.5, 1.0, 1.0), "ourTexture", GL_TEXTURE10));
	//material.push_back(JUMA_materialFracture(NULL, JUMA_color(0.2, 0, 0.7, 1.0), "mixCol", GL_TEXTURE1));
	JUMA_AudioChannel channel1;
	channel1.loadChunk("./music/Big Smoke - Moan.wav","smoke");
	glm::mat4 model, view, proj;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
	proj = glm::perspective(45.0f, (float)(600 / 600), 0.1f, 500.0f);
	//JUMA_GO testObject(JUMA_RECTANGLE, material, 10.0f, "model",view,"view",proj,"projection" );
	
	std::vector<GLfloat> graph;
	GLuint graphVBO, graphVAO;
	JUMA_GO go(JUMA_GO_RECT, material, 10.0f, "model", view, "view", proj, "projection");
	int i = 0;
	while (1) {
		//std::cout << glGetError();
		if (i < 100) {
			graph.push_back(i/100);
	
		}
		SDL_PollEvent(NULL);
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		glClearColor(0, 0, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (keystate[SDL_SCANCODE_UP])
			go.translate(0.0, 0.01, 0.0);
		if (keystate[SDL_SCANCODE_LEFT])
			go.translate(-0.01, 0.0, 0.0);
		if (keystate[SDL_SCANCODE_RIGHT])
			go.translate(0.01, 0.0, 0.0);
		if (keystate[SDL_SCANCODE_DOWN])
			go.translate(0.0, -0.01, 0.0);
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
			go.translate(0.0, 0.0, +0.01);
		if (keystate[SDL_SCANCODE_2])
			go.translate(0.0, 0.0, -0.01);
		if (keystate[SDL_SCANCODE_SPACE])
			channel1.playChunk("smoke");
		
		view = glm::mat4();
		proj = glm::mat4();
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		proj = glm::perspective(45.0f, (float)(600 / 600), 0.1f, 100.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//drawRectangle(basic, "model", x, y, z, xr, yr, 0.0f, 0.5f, 0.5f, 0.5f);
		//drawRectangle3D(basic,material, JUMA_MakeCollection(model, view, proj, "model", "view", "projection"), x, y, z, xr, yr, 0.0, 1, 1, 1);
		//drawTriangle3D(basic, JUMA_MakeCollection(model, view, proj, "model", "view", "projection"), x+0.9,y+0.1, z, xr, yr, 0.0f, 0.5f, 0.5f, 0.5f);
		go.setPos(0.0, 0.0, 0.0);
		go.draw(basic);
		SDL_GL_SwapWindow(renderEssentials.window);
		SDL_Delay(10);
	}
	return 1;
}