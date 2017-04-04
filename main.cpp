#pragma once
//Opengl includes
#include "./libraries/include/GL/glew.h"
//SDL includes
#include "./libraries/include/SDL.h"
#include "./libraries/include/SDL_opengl.h"
#include <math.h>
#include <ctime>
#include <time.h>

#include "./engineFiles/headers/JUMA_gameObject.h"
#include "./engineFiles/headers/JUMA_liftoff.h"
#include "./engineFiles/headers/JUMA_shapes.h"
#include "./engineFiles/headers/JUMA_shaders.h"
#include "./engineFiles/headers/JUMA_textures.h"
#include "./engineFiles/headers/JUMA_materials.h"
#include "./engineFiles/headers//JUMA_font.h"
#include "./engineFiles/headers/JUMA_audio.h"
#include <JUMA_camera.h>
#define WIDTH 600
#define HEIGHT 600
static glm::vec3 castRay(int x,int y,glm::mat4 projection,glm::mat4 view){
     float xf = (2.0f * x) / (WIDTH*2) - 1.0f;
    float yf = 1.0f - (2.0f * y) / (HEIGHT*2);

    glm::mat4 invVP = glm::inverse(projection * view);
    glm::vec4 screenPos = glm::vec4(xf, yf*-1, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;
    glm::vec3 dir = glm::normalize(glm::vec3(worldPos));
    return dir;
}

class Main {
private:
	JUMA_GO writing_object;
	JUMA_Font testFont;
	JUMA_material mat;
	JUMA_RenderES renderingEssentials;
	JUMA_Mat3DCollectPlus collection;
	JUMA_Shader texture_basic;
	JUMA_Camera cam1;
	SDL_Color col;
public:
	Main() {
        cam1 = JUMA_Camera(0,0,-3,45,400,0.2,WIDTH,HEIGHT);
        renderingEssentials = initJUMA(WIDTH, HEIGHT, "sceneGraph");
		col.r = 255;
		col.b = 0;
		col.g = 0;
		col.a = 255;
		JUMA_Texture temp = JUMA_Texture("./textures/container2.png",GL_TEXTURE_2D,GL_LINEAR);
		mat.push_back(JUMA_materialFracture(&temp,JUMA_color(0,0,0,1),"mytexture",GL_TEXTURE0));
		writing_object = JUMA_GO(JUMA_GO_CUBE,mat,100,"model",cam1.getView(),"view",cam1.getProj(),"projection");
        texture_basic = JUMA_Shader("./shaders/texture/texture.vs", "./shaders/texture/texture.frag");
        glEnable(GL_DEPTH_TEST);
        srand(time(NULL));
	}
	int update() {
		clock_t start = clock();
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		SDL_PollEvent(NULL);
		glClearColor(0.6, 0.6, 0.8, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        writing_object.transform.setPos(sin(clock()/(float)CLOCKS_PER_SEC)/2,sin(clock()/(float)CLOCKS_PER_SEC)/3,sin(clock()/(float)CLOCKS_PER_SEC)/2.5);

        writing_object.transform.setRot(sin(clock()/(float)CLOCKS_PER_SEC)/2,cos(clock()/(float)CLOCKS_PER_SEC),sin(clock()/(float)CLOCKS_PER_SEC)*2);
        writing_object.draw(texture_basic);
		SDL_GL_SwapWindow(renderingEssentials.window);
		return 1;
	}
	int destroy() {
		return 1;
	}



};
