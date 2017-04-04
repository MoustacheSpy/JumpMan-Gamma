#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <JUMA_textures.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <JUMA_shaders.h>
#include <JUMA_shapes.h>
#include <JUMA_gameObject.h>

//JUMA_Shader text("./shaders/text/text.vs", "./shaders/text/text.frag");
class JUMA_Font {
private:
	SDL_Surface *sourceSurface;
	TTF_Font *font;
	int type;
	GLuint Texture;
	JUMA_GO object;
	JUMA_material mat;

public:

	JUMA_Font() {};
	JUMA_Font(char *path, int size, SDL_Color color, char* text,char *uniform);
	int changeText(const char* text, SDL_Color color);
		JUMA_Texture convertToTexture() {
		JUMA_Texture _this;
		SDL_SaveBMP(sourceSurface, "kk.bmp");
		std::cout << "Expected " << sourceSurface;
		_this.id = _this.loadFromSurface(sourceSurface,GL_TEXTURE_2D,GL_NEAREST);

		return _this;
	}

};
