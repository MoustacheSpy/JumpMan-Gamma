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

#define TETRIS_A 1
#define Tetris_a_width 2
#define Tetris_a_height 2

#define TETRIS_B 2
#define Tetris_b_width 2
#define Tetris_b_height 3

#define TETRIS_C 3
#define Tetris_c_width 2
#define Tetris_c_height 3

#define TETRIS_D 4
#define Tetris_d_width 3
#define Tetris_d_height 2

#define TETRIS_E 5
#define Tetris_e_width 3
#define Tetris_e_height 2

#define TETRIS_F 6
#define Tetris_f_width 3
#define Tetris_f_height 2

#define TETRIS_G 7
#define Tetris_g_width 1
#define Tetris_g_height 4

#define gridWidth 10
#define gridHeight 20
/*struct Tetris {
	JUMA_GO object;
	char State1[4][4];
	char State2[4][4];
	char State3[4][4];
	char State4[4][4];
};

Tetris loadTetris(char *filePath,glm::mat4 view, glm::mat4 proj) {
	char texturePath[100];
	FILE *fp = fopen(filePath, "r");
	Tetris tetris;
	fscanf(fp, "%s\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n\n", texturePath, tetris.State1[0][0], tetris.State1[1][0], tetris.State1[2][0], tetris.State1[3][0], tetris.State1[4][0], tetris.State1[0][1], tetris.State1[1][1], tetris.State1[2][1], tetris.State1[3][1], tetris.State1[4][1], tetris.State1[0][2], tetris.State1[1][2], tetris.State1[2][2], tetris.State1[3][2], tetris.State1[4][2], tetris.State1[0][3], tetris.State1[1][3], tetris.State1[2][3], tetris.State1[3][3], tetris.State1[4][3], tetris.State1[0][4], tetris.State1[1][4], tetris.State1[2][4], tetris.State1[3][4], tetris.State1[4][4], &tetris.State2[0][0], &tetris.State2[1][0], &tetris.State2[2][0], &tetris.State2[3][0], &tetris.State2[4][0], &tetris.State2[0][1], &tetris.State2[1][1], &tetris.State2[2][1], &tetris.State2[3][1], &tetris.State2[4][1], &tetris.State2[0][2], &tetris.State2[1][2], &tetris.State2[2][2], &tetris.State2[3][2], &tetris.State2[4][2], &tetris.State2[0][3], &tetris.State2[1][3], &tetris.State2[2][3], &tetris.State2[3][3], &tetris.State2[4][3], &tetris.State2[0][4], &tetris.State2[1][4], &tetris.State2[2][4], &tetris.State2[3][4], &tetris.State2[4][4], &tetris.State3[0][0], &tetris.State3[1][0], &tetris.State3[2][0], &tetris.State3[3][0], &tetris.State3[4][0], &tetris.State3[0][1], &tetris.State3[1][1], &tetris.State3[2][1], &tetris.State3[3][1], &tetris.State3[4][1], &tetris.State3[0][2], &tetris.State3[1][2], &tetris.State3[2][2], &tetris.State3[3][2], &tetris.State3[4][2], &tetris.State3[0][3], &tetris.State3[1][3], &tetris.State3[2][3], &tetris.State3[3][3], &tetris.State3[4][3], &tetris.State3[0][4], &tetris.State3[1][4], &tetris.State3[2][4], &tetris.State3[3][4], &tetris.State3[4][4], &tetris.State4[0][0], &tetris.State4[1][0], &tetris.State4[2][0], &tetris.State4[3][0], &tetris.State4[4][0], &tetris.State4[0][1], &tetris.State4[1][1], &tetris.State4[2][1], &tetris.State4[3][1], &tetris.State4[4][1], &tetris.State4[0][2], &tetris.State4[1][2], &tetris.State4[2][2], &tetris.State4[3][2], &tetris.State4[4][2], &tetris.State4[0][3], &tetris.State4[1][3], &tetris.State4[2][3], &tetris.State4[3][3], &tetris.State4[4][3], &tetris.State4[0][4], &tetris.State4[1][4], &tetris.State4[2][4], &tetris.State4[3][4], &tetris.State4[4][4]);
	JUMA_Texture tetrisBlockTex_2(texturePath, GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_2;
	tetrisBlock_2.push_back(JUMA_materialFracture(&tetrisBlockTex_2, JUMA_color(0, 0, 0, 0), "texture", GL_TEXTURE0));
	JUMA_GO tetris_2(JUMA_RECTANGLE, tetrisBlock_2, 12, "model", view, "view", proj, "projection");
	tetris.object = tetris_2;
	return tetris;
}
*/

void insertTetris(int tetrisx,int tetrisy,int gameGrid[][gridWidth],char tetrisID, int tetris[][4]) {
	int x, y;
	switch(tetrisID) {
		case TETRIS_A:
			for (x = 0; x < Tetris_a_height; x++) {
				for (y = 0; y < Tetris_a_width; y++) {
					gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
				}
			}
			break;
		case TETRIS_B:
			for (x = 0; x < Tetris_b_height; x++) {
				for (y = 0; y < Tetris_b_width; y++) {
					gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
				}
			}
			break;
		case TETRIS_C:
			for (x = 0; x < Tetris_c_height; x++) {
				for (y = 0; y < Tetris_c_width; y++) {
					gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
				}
			}
			break;
		case TETRIS_D:
			for (x = 0; x < Tetris_d_height; x++) {
				for (y = 0; y < Tetris_d_width; y++) {
					gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
				}
			}
			break;
		case TETRIS_E:
			for (x = 0; x < Tetris_e_height; x++) {
				for (y = 0; y < Tetris_e_width; y++) {
					gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
				}
			}
			break;
		case TETRIS_F:
			for (x = 0; x < Tetris_f_height; x++) {
				for (y = 0; y < Tetris_f_width; y++) {
					gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
				}
			}
			break;
		case TETRIS_G:
			for (x = 0; x < Tetris_g_height; x++) {
				for (y = 0; y < Tetris_g_width; y++) {
					gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
				}
			}
			break;

	}


}


/*
void drawGrid(JUMA_Shader shader,float x, float y, float x2, float y2, float cellSize) {
	float xi = x, yi = y;
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	JUMA_Mat3DCollect collection;
	collection.view = glm::translate(collection.view, glm::vec3(0.0f, 0.0f, -5.0f));
	collection.proj = glm::perspective(45.0f, (float)(600 / 600), 0.1f, 500.0f);
	strcpy(collection.modelName, "model");
	strcpy(collection.projName, "projection");
	strcpy(collection.viewName, "view");
	GLuint k = 123123;
	JUMA_material rectMat;
	rectMat.push_back(JUMA_materialFracture(&k, JUMA_color(0, 0, 0, 0), "color", GL_TEXTURE0));
	
	for (xi = x; xi < x2; xi += cellSize) {
		for (yi = y; yi < y2; yi += cellSize) {
			drawRectangle3D(shader,rectMat,collection,xi,yi,0.0,0.0,0.0,0.0,cellSize,cellSize,cellSize);
			printf("draw");
		}
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
*/

int main(int argc, char* args[])
{
	//Initializing Game Variables
	int gameGrid[gridHeight][gridWidth]{
		{7,7,7,7,7,7,7,7,7,7},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{4,0,0,0,0,0,0,0,0,6},
		{5,5,5,5,5,5,5,5,5,5}
	};
	int Tetris_A[][4] = {
		{1,1,0,0},
		{1,1,0,0}
	};
	int Tetris_B[][4] = {
		{ 2,0,0,0 },
		{ 2,0,0,0 },
		{ 2,2,0,0 }
	};
	int Tetris_C[][4] = {
		{ 0,3,0,0 },
		{ 0,3,0,0 },
		{ 3,3,0,0 }
	};
	int Tetris_D[][4] = {
		{ 0,4,4,0 },
		{ 4,4,0,0 }
	};
	int Tetris_E[][4] = {
		{ 5,5,0,0 },
		{ 0,5,5,0 }
	};
	int Tetris_F[][4] = {
		{ 6,6,6,0 },
		{ 0,6,0,0 }
	};
	int Tetris_G[][4] = {
		{ 7,0,0,0 },
		{ 7,0,0,0 },
		{ 7,0,0,0 },
		{ 7,0,0,0 }
	};



	//Initializing Visual Variables
	//Initializing Rendering Essentials
	JUMA_RenderES renderEssentials;
	renderEssentials=initJUMA(600,600, "JUMPMAN_V1");
	//___________________________________
	///Initializing shapes for drawing the grid
	//initShapes(JUMA_RECTANGLE);
	//___________________________________
	//Initializing GO
	///tetris_A
	glm::mat4 model, view, proj;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
	proj = glm::perspective(45.0f, (float)(600 / 600), 0.1f, 500.0f);


	
	
	JUMA_Texture tetrisBlockTex_1("./textures/tetris/blocks/tetris1.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_1;
	SDL_Color black;
	black.r = 255;
	black.g = 255;
	black.b = 255;
	black.a = 255;
	//JUMA_Font font("./fonts/Time_Roman.ttf", 30, black, "test");
	tetrisBlock_1.push_back(JUMA_materialFracture(&tetrisBlockTex_1, JUMA_color(0, 0, 0, 0), "texture", GL_TEXTURE0));
	JUMA_GO tetris_1(JUMA_RECTANGLE, tetrisBlock_1, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_2("./textures/tetris/blocks/tetris2.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_2;
	tetrisBlock_2.push_back(JUMA_materialFracture(&tetrisBlockTex_2, JUMA_color(0, 0, 0, 0), "texture", GL_TEXTURE0));
	JUMA_GO tetris_2(JUMA_RECTANGLE, tetrisBlock_2, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_3("./textures/tetris/blocks/tetris3.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_3;
	tetrisBlock_3.push_back(JUMA_materialFracture(&tetrisBlockTex_3, JUMA_color(0, 0, 0, 0), "texture", GL_TEXTURE0));
	JUMA_GO tetris_3(JUMA_RECTANGLE, tetrisBlock_3, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_4("./textures/tetris/blocks/tetris4.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_4;
	tetrisBlock_4.push_back(JUMA_materialFracture(&tetrisBlockTex_4, JUMA_color(0, 0, 0, 0), "texture", GL_TEXTURE0));
	JUMA_GO tetris_4(JUMA_RECTANGLE, tetrisBlock_4, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_5("./textures/tetris/blocks/tetris5.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_5;
	tetrisBlock_5.push_back(JUMA_materialFracture(&tetrisBlockTex_5, JUMA_color(0, 0, 0, 0), "texture", GL_TEXTURE0));
	JUMA_GO tetris_5(JUMA_RECTANGLE, tetrisBlock_5, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_6("./textures/tetris/blocks/tetris6.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_6;
	tetrisBlock_6.push_back(JUMA_materialFracture(&tetrisBlockTex_6, JUMA_color(0, 0, 0, 0), "texture", GL_TEXTURE0));
	JUMA_GO tetris_6(JUMA_RECTANGLE, tetrisBlock_6, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_7("./textures/tetris/blocks/tetris7.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_7;
	tetrisBlock_7.push_back(JUMA_materialFracture(&tetrisBlockTex_7, JUMA_color(0, 0, 0, 0), "texture", GL_TEXTURE0));
	JUMA_GO tetris_7(JUMA_RECTANGLE, tetrisBlock_7, 12, "model", view, "view", proj, "projection");

	//setting scale
	tetris_1.setScale_texture();
	tetris_2.setScale_texture();
	tetris_3.setScale_texture();
	tetris_4.setScale_texture();
	tetris_5.setScale_texture();
	tetris_6.setScale_texture();
	tetris_7.setScale_texture();
	//__________________________________
	//Initializing shaders
	JUMA_Shader texture_basic("./shaders/texture/texture.vs", "./shaders/texture/texture.frag");
	//__________________________________
	//GameLoop

	int x = 0, y = 0;

	bool enabled = false;
	float gridx = +20.0, gridy = -20.0;
	insertTetris(2, 3, gameGrid, TETRIS_C, Tetris_C);
	Tetris test1 = loadTetris("./textures/tetris/blocks/tetris1.tetris", view, proj);
	
	test1.object.draw(texture_basic);
	while (1) {
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		SDL_PollEvent(NULL);
		glClearColor(0, 0, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float cellSize = 2;
		
		for (y = 0; y < gridHeight; y++) {
			for (x = 0; x < gridWidth; x++) {
				printf("%d", gameGrid[y][x]);
				switch (gameGrid[y][x]) {
					case 1:
						tetris_1.setPos(((float)x)*cellSize-gridx, ((float)y*-1)*cellSize-gridy, 0.0);
						tetris_1.draw(texture_basic);
						break;
					case 2:
						tetris_2.setPos(((float)x)*cellSize - gridx, ((float)y*-1)*cellSize - gridy, 0.0);
						tetris_2.draw(texture_basic);
						break;
					case 3:
						tetris_3.setPos(((float)x)*cellSize - gridx, ((float)y*-1)*cellSize - gridy, 0.0);
						tetris_3.draw(texture_basic);
						break;
					case 4:
						tetris_4.setPos(((float)x)*cellSize - gridx, ((float)y*-1)*cellSize - gridy, 0.0);
						tetris_4.draw(texture_basic);
						break;
					case 5:
						tetris_5.setPos(((float)x)*cellSize - gridx, ((float)y*-1)*cellSize - gridy, 0.0);
						tetris_5.draw(texture_basic);
						break;
					case 6:
						tetris_6.setPos(((float)x)*cellSize - gridx, ((float)y*-1)*cellSize - gridy, 0.0);
						tetris_6.draw(texture_basic);
						break;
					case 7:
						tetris_7.setPos(((float)x)*cellSize - gridx, ((float)y*-1)*cellSize - gridy, 0.0);
						tetris_7.draw(texture_basic);
						break;
				}
			}
			printf("\n");
		}
		printf("x:%f y:%", gridx, gridy);
		system("cls");
		if (keystate[SDL_SCANCODE_UP])
			gridy += 0.1;
		if (keystate[SDL_SCANCODE_DOWN]) 
			gridy -= 0.1;
	
		if (keystate[SDL_SCANCODE_RIGHT])
			gridx += 0.1;
		if (keystate[SDL_SCANCODE_LEFT])
			gridx -= 0.1;
		
		//drawGrid(texture_basic, -1, -1, 1, 1, 0.2);
		SDL_GL_SwapWindow(renderEssentials.window);
		SDL_Delay(10);
	}
}