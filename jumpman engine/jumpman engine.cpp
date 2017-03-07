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
#include <time.h>

//JUMA includes
#include "./engineFiles/headers/JUMA_gameObject.h"
#include "./engineFiles/headers/JUMA_liftoff.h"
#include "./engineFiles/headers/JUMA_shapes.h"
#include "./engineFiles/headers/JUMA_shaders.h"
#include "./engineFiles/headers/JUMA_textures.h"
#include "./engineFiles/headers/JUMA_materials.h"
#include "./engineFiles/headers/JUMA_font.h"
#include "./engineFiles/headers/JUMA_audio.h"

#define TETRIS_A 1
#define Tetris_a_width 4
#define Tetris_a_height 4

#define TETRIS_B 2
#define Tetris_b_width 4
#define Tetris_b_height 5

#define TETRIS_C 3
#define Tetris_c_width 4
#define Tetris_c_height 5

#define TETRIS_D 4
#define Tetris_d_width 5
#define Tetris_d_height 4

#define TETRIS_E 5
#define Tetris_e_width 5
#define Tetris_e_height 4

#define TETRIS_F 6
#define Tetris_f_width 5
#define Tetris_f_height 4

#define TETRIS_G 7
#define Tetris_g_width 3
#define Tetris_g_height 6

#define gridWidth 10
#define gridHeight 20


void insertTetris(int tetrisx, int tetrisy, int gameGrid[][gridWidth], char tetrisID, int tetris[][6], bool writeHbox) {
	int x, y;
	switch (tetrisID) {
	case TETRIS_A:
		for (x = 0; x < Tetris_a_height; x++) {
			for (y = 0; y < Tetris_a_width; y++) {
				if (gameGrid[x + tetrisx][y + tetrisy] == 0)
					if (writeHbox)
						gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
					else
						if (tetris[x][y] < 8)
							gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
			}
		}
		break;
	case TETRIS_B:
		for (x = 0; x < Tetris_b_height; x++) {
			for (y = 0; y < Tetris_b_width; y++) {
				if (gameGrid[x + tetrisx][y + tetrisy] == 0)
					if (writeHbox)
						gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
					else
						if (tetris[x][y] < 8)
							gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
			}
		}
		break;
	case TETRIS_C:
		for (x = 0; x < Tetris_c_height; x++) {
			for (y = 0; y < Tetris_c_width; y++) {
				if (gameGrid[x + tetrisx][y + tetrisy] == 0)
					if (writeHbox)
						gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
					else
						if (tetris[x][y] < 8)
							gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
			}
		}
		break;
	case TETRIS_D:
		for (x = 0; x < Tetris_d_height; x++) {
			for (y = 0; y < Tetris_d_width; y++) {
				if (gameGrid[x + tetrisx][y + tetrisy] == 0)
					if (writeHbox)
						gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
					else
						if (tetris[x][y] < 8)
							gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
			}
		}
		break;
	case TETRIS_E:
		for (x = 0; x < Tetris_e_height; x++) {
			for (y = 0; y < Tetris_e_width; y++) {
				if (gameGrid[x + tetrisx][y + tetrisy] == 0)
					if (writeHbox)
						gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
					else
						if (tetris[x][y] < 8)
							gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
			}
		}
		break;
	case TETRIS_F:
		for (x = 0; x < Tetris_f_height; x++) {
			for (y = 0; y < Tetris_f_width; y++) {
				if (gameGrid[x + tetrisx][y + tetrisy] == 0)
					if (writeHbox)
						gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
					else
						if (tetris[x][y] < 8)
							gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
			}
		}
		break;
	case TETRIS_G:
		for (x = 0; x < Tetris_g_height; x++) {
			for (y = 0; y < Tetris_g_width; y++) {
				if (gameGrid[x + tetrisx][y + tetrisy] == 0)
					if (writeHbox)
						gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
					else
						if (tetris[x][y] < 8)
							gameGrid[x + tetrisx][y + tetrisy] = tetris[x][y];
			}
		}
		break;

	}


}

void clearTable(int gameGrid[][gridWidth]) {
	int x, y;
	for (x = 0; x < gridHeight; x++) {
		for (y = 0; y < gridWidth; y++) {
			gameGrid[x][y] = 0;
			//printf("%d ", gameGrid[x][y]);
		}
		//printf("\n");
	}

}


int main(int argc, char* args[])
{
	//Initializing Game Variables
	int gameGrid[gridHeight][gridWidth]{
		{7,7,7,0,0,0,0,7,7,7},
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
	int playerGrid[gridHeight][gridWidth]{
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 }

	};
	int Tetris_A[][6] = {
		{0,8,8,0},
		{8,1,1,9},
		{8,1,1,9},
		{0,10,10,0},
		{ 0,0,0,0 },
		{ 0,0,0,0 }

	};
	int Tetris_B[][6] = {
		{ 0,8,0,0 },
		{ 8,2,9,0 },
		{ 8,2,9,0 },
		{ 8,2,2,9 },
		{ 0,10,10,0 },
	};
	int Tetris_C[][6] = {
		{ 0,0,8,0 },
		{ 0,8,3,9 },
		{ 0,8,3,9 },
		{ 8,3,3,9 },
		{ 0,10,10,0 },
	};
	int Tetris_D[][6] = {
		{ 0,0,8,8,0 },
		{ 0,8,4,4,9 },
		{ 8,4,4,11,0 },
		{ 0,10,10,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 }
	};
	int Tetris_E[][6] = {
		{ 0,8,8,0,0 },
		{ 8,5,5,9,0 },
		{ 0,12,5,5,9 },
		{ 0,0,10,10,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 }
	};
	int Tetris_F[][6] = {
		{ 0,8,8,8,0 },
		{ 8,6,6,6,9 },
		{ 0,12,6,11,0 },
		{ 0,0,10,0,0 },
		{0,0,0,0,0},
		{ 0,0,0,0,0 }

	};
	int Tetris_G[][6] = {
		{ 0,8,0 },
		{ 8,7,9 },
		{ 8,7,9 },
		{ 8,7,9 },
		{ 8,7,9 },
		{ 0,10,0 }
	};



	//Initializing Visual Variables
	//Initializing Rendering Essentials
	JUMA_RenderES renderEssentials;
	renderEssentials = initJUMA(600, 600, "JUMPMAN_V1");
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
	JUMA_Font font("./fonts/Time_Roman.ttf", 30, black, "test");

	tetrisBlock_1.push_back(JUMA_materialFracture(&tetrisBlockTex_1, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO tetris_1(JUMA_RECTANGLE, tetrisBlock_1, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_2("./textures/tetris/blocks/tetris2.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_2;
	tetrisBlock_2.push_back(JUMA_materialFracture(&tetrisBlockTex_2, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO tetris_2(JUMA_RECTANGLE, tetrisBlock_2, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_3("./textures/tetris/blocks/tetris3.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_3;
	tetrisBlock_3.push_back(JUMA_materialFracture(&tetrisBlockTex_3, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO tetris_3(JUMA_RECTANGLE, tetrisBlock_3, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_4("./textures/tetris/blocks/tetris4.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_4;
	tetrisBlock_4.push_back(JUMA_materialFracture(&tetrisBlockTex_4, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO tetris_4(JUMA_RECTANGLE, tetrisBlock_4, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_5("./textures/tetris/blocks/tetris5.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_5;
	tetrisBlock_5.push_back(JUMA_materialFracture(&tetrisBlockTex_5, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO tetris_5(JUMA_RECTANGLE, tetrisBlock_5, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_6("./textures/tetris/blocks/tetris6.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_6;
	tetrisBlock_6.push_back(JUMA_materialFracture(&tetrisBlockTex_6, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO tetris_6(JUMA_RECTANGLE, tetrisBlock_6, 12, "model", view, "view", proj, "projection");

	JUMA_Texture tetrisBlockTex_7("./textures/tetris/blocks/tetris7.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material tetrisBlock_7;
	tetrisBlock_7.push_back(JUMA_materialFracture(&tetrisBlockTex_7, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO tetris_7(JUMA_RECTANGLE, tetrisBlock_7, 12, "model", view, "view", proj, "projection");

	JUMA_Texture hitbox_tex("./textures/tetris/blocks/tetris8.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material hitbox_mat;
	hitbox_mat.push_back(JUMA_materialFracture(&hitbox_tex, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO hitbox(JUMA_RECTANGLE, hitbox_mat, 12, "model", view, "view", proj, "projection");

	JUMA_Texture hitbox_bottom_tex("./textures/tetris/blocks/tetris9.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material hitbox_bottom_mat;
	hitbox_bottom_mat.push_back(JUMA_materialFracture(&hitbox_bottom_tex, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO hitbox_bottom(JUMA_RECTANGLE, hitbox_bottom_mat, 12, "model", view, "view", proj, "projection");

	JUMA_Texture hitbox_bottom_combi_tex("./textures/tetris/blocks/tetris10.png", GL_TEXTURE_2D, GL_NEAREST, GL_CLAMP_TO_BORDER, SOIL_LOAD_RGBA, GL_RGBA);
	JUMA_material hitbox_bottom_combi_mat;
	hitbox_bottom_combi_mat.push_back(JUMA_materialFracture(&hitbox_bottom_combi_tex, JUMA_color(0, 0, 0, 0), "mytexture", GL_TEXTURE0));
	JUMA_GO hitbox_bottom_combi(JUMA_RECTANGLE, hitbox_bottom_combi_mat, 12, "model", view, "view", proj, "projection");

	JUMA_GO cube(JUMA_GO_CUBE, hitbox_bottom_combi_mat, 12, "model", view, "view", proj, "projection");
	//setting scale
	tetris_1.setScale_texture();
	tetris_2.setScale_texture();
	tetris_3.setScale_texture();
	tetris_4.setScale_texture();
	tetris_5.setScale_texture();
	tetris_6.setScale_texture();
	tetris_7.setScale_texture();
	hitbox.setScale_texture();
	hitbox_bottom.setScale_texture();
	hitbox_bottom_combi.setScale_texture();
	//__________________________________
	//Initializing shaders
	JUMA_Shader texture_basic("./shaders/pbr/pbr.vs", "./shaders/pbr/pbr.frag");
	//__________________________________
	//GameLoop

	int x = 0, y = 0;
	int px = 0, py = 2;
	int framecount = 1;
	bool enabled = false;
	float gridx = +20.0, gridy = -20.0;
	bool leftBlock = false, rightBlock = false, bottomBlock = false, upBlock = false;
	bool leftScanBlock = false, rightScanBlock = false, downScanBlock = false;
	bool change = false;
	float FPS = 1;
	srand(time(NULL));
	char selected = rand() % 7 + 1;

	glEnable(GL_DEPTH_TEST);
	while (1) {
		// Get the start time here
		clock_t start = clock();
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		SDL_PollEvent(NULL);
		glClearColor(0, 0, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		clearTable(playerGrid);
		float cellSize = 2;
		//font.draw(returnContainer(),0.0, 0.0);
		switch (selected)
		{
		case TETRIS_A:
			insertTetris(px, py, playerGrid, selected, Tetris_A, true);
			break;
		case TETRIS_B:
			insertTetris(px, py, playerGrid, selected, Tetris_B, true);
			break;
		case TETRIS_C:
			insertTetris(px, py, playerGrid, selected, Tetris_C, true);
			break;
		case TETRIS_D:
			insertTetris(px, py, playerGrid, selected, Tetris_D, true);
			break;
		case TETRIS_E:
			insertTetris(px, py, playerGrid, selected, Tetris_E, true);
			break;
		case TETRIS_F:
			insertTetris(px, py, playerGrid, selected, Tetris_F, true);
			break;
		case TETRIS_G:
			insertTetris(px, py, playerGrid, selected, Tetris_G, true);
			break;
		}

		if (!bottomBlock&&framecount % 30 == 0 || keystate[SDL_SCANCODE_DOWN] && !bottomBlock) {
			change = true;
		}
		for (y = 0; y < gridHeight; y++) {
			for (x = 0; x < gridWidth; x++) {
				//printf("%d", playerGrid[y][x]);

				switch (playerGrid[y][x]) {
				case 1:
					tetris_2.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_2.draw(texture_basic);
					break;
				case 2:
					tetris_2.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_2.draw(texture_basic);
					break;
				case 3:
					tetris_3.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_3.draw(texture_basic);
					break;
				case 4:
					tetris_4.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_4.draw(texture_basic);
					break;
				case 5:
					tetris_5.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_5.draw(texture_basic);
					break;
				case 6:
					tetris_6.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_6.draw(texture_basic);
					break;
				case 7:
					tetris_7.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_7.draw(texture_basic);
					break;
				case 8:
					hitbox.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					//hitbox.draw(texture_basic);
					if (!leftScanBlock)
						if (gameGrid[y][x] != 0 && gameGrid[y][x] < 8) {
							leftBlock = true;
							leftScanBlock = true;
						}
						else leftBlock = false;

						break;
				case 9:
					hitbox.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					//hitbox.draw(texture_basic);
					if (!rightScanBlock)
						if (gameGrid[y][x] != 0 && gameGrid[y][x] < 8) {
							rightBlock = true;
							rightScanBlock = true;
						}
						else rightBlock = false;

						break;
				case 10:
					hitbox_bottom.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					//hitbox_bottom.draw(texture_basic);
					if (change) {
						if (!downScanBlock)
							if (gameGrid[y][x] != 0 && gameGrid[y][x] < 8) {
								bottomBlock = true;
								downScanBlock = true;

							}
					}
					break;
				case 11:
					hitbox_bottom_combi.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					//hitbox_bottom_combi.draw(texture_basic);
					if (!downScanBlock || !rightScanBlock)
						if (gameGrid[y][x] != 0 && gameGrid[y][x] < 8) {
							if (change) {
								bottomBlock = true;
								downScanBlock = true;
							}
							rightBlock = true;
							rightScanBlock = true;
						}

					break;
				case 12:
					hitbox_bottom_combi.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					//hitbox_bottom_combi.draw(texture_basic);
					if (!downScanBlock || !rightScanBlock)
						if (gameGrid[y][x] != 0 && gameGrid[y][x] < 8) {
							if (change) {
								bottomBlock = true;
								downScanBlock = true;
							}
							leftBlock = true;
							leftScanBlock = true;
						}

					break;
				}
				switch (gameGrid[y][x]) {
				case 1:
					tetris_2.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_2.draw(texture_basic);
					break;
				case 2:
					tetris_2.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_2.draw(texture_basic);
					break;
				case 3:
					tetris_3.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_3.draw(texture_basic);
					break;
				case 4:
					tetris_4.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_4.draw(texture_basic);
					break;
				case 5:
					tetris_5.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_5.draw(texture_basic);
					break;
				case 6:
					tetris_6.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_6.draw(texture_basic);
					break;
				case 7:
					tetris_7.setPos(((float)(x))*cellSize - gridx, ((float)(y)*-1)*cellSize - gridy, 0.0);
					tetris_7.draw(texture_basic);
					break;
				}

			}
			//printf("\n");
		}
		//printf("x:%f y:%", gridx, gridy);
		//system("cls");

		change = false;
		rightScanBlock = downScanBlock = leftScanBlock = false;
		if (!bottomBlock&&framecount % 30 == 0) {
			px++;
			framecount = 1;

		}

		if (keystate[SDL_SCANCODE_UP] && px > 0) {
			if (enabled) {
				px--;
				enabled = false;
			}
		}
		else {
			if (keystate[SDL_SCANCODE_DOWN] && !bottomBlock) {
				if (enabled) {
					px++;
					enabled = false;

					framecount = 1;
				}
			}
			else {
				if (keystate[SDL_SCANCODE_RIGHT] && !rightBlock && !bottomBlock) {
					if (enabled) {
						py++;
						enabled = false;
					}
				}
				else {
					if (keystate[SDL_SCANCODE_LEFT] && !leftBlock && !bottomBlock) {
						if (enabled) {
							py--;
							enabled = false;
						}
					}
					else enabled = true;
				}
			}
		}
		if (bottomBlock) {


			switch (selected)
			{
			case TETRIS_A:
				insertTetris(px, py, gameGrid, selected, Tetris_A, false);
				break;
			case TETRIS_B:
				insertTetris(px, py, gameGrid, selected, Tetris_B, false);
				break;
			case TETRIS_C:
				insertTetris(px, py, gameGrid, selected, Tetris_C, false);
				break;
			case TETRIS_D:
				insertTetris(px, py, gameGrid, selected, Tetris_D, false);
				break;
			case TETRIS_E:
				insertTetris(px, py, gameGrid, selected, Tetris_E, false);
				break;
			case TETRIS_F:
				insertTetris(px, py, gameGrid, selected, Tetris_F, false);
				break;
			case TETRIS_G:
				insertTetris(px, py, gameGrid, selected, Tetris_G, false);
				break;
			}
			srand(time(NULL));
			selected = rand() % 7 + 1;
			px = 0;
			py = 2;
			leftBlock = rightBlock = bottomBlock = false;

		}
		//cube.setPos(1.5, 1.4, 0);
		cube.draw(texture_basic);


		cube.setPos(sin((clock() * 1000 / CLOCKS_PER_SEC) / 200.0) / 10.0 + 1.5, cos((clock() * 1000 / CLOCKS_PER_SEC) / 800.0) / 10.0 + 1.5, sin((clock() * 1000 / CLOCKS_PER_SEC) / 500.0) / 10.0);
		cube.setRot(sin((clock() * 1000 / CLOCKS_PER_SEC) / 200.0) / 10.0 , cos((clock() * 1000 / CLOCKS_PER_SEC) / 800.0) / 10.0 , sin((clock() * 1000 / CLOCKS_PER_SEC) / 500.0) / 10.0);
		printf("%d %d\n", px, py);
		//drawGrid(texture_basic, -1, -1, 1, 1, 0.2);
		SDL_GL_SwapWindow(renderEssentials.window);




		// Do stuff

		// While clock didn't elapse, do nothing, because the lowest sleeping time is 10 ms
		// You want higher resolution than that.
		// Sleep time is 16 ms because 1 / 60fps = ~16.66ms
		while (((clock() - start) * 1000 / CLOCKS_PER_SEC) < 16)
			;

		// Time in milliseconds which took the loop to complete
		float MS = (float)((clock() - start) * 1000 / CLOCKS_PER_SEC);
		// Time in seconds
		float S = MS / 1000.0f;
		// Frames per seconds
		FPS = 1000.0f / MS;
		framecount++;
	}
}