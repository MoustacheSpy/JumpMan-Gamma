#include "stdafx.h"
#include <JUMA_textures.h>
#include <SDL.h>
#include <SDL_image.h>

GLuint JUMA_Texture::loadFromSurface(SDL_Surface *img, GLenum target, GLenum filtering) {
	GLuint TextureID = 0;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	if (target == GL_TEXTURE_2D)
	{
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	int Mode = GL_RGB;
	if (img->format->BytesPerPixel == 4) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		transparent = true;
		Mode = GL_RGBA;
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, Mode, img->w, img->h, 0, Mode, GL_UNSIGNED_BYTE, img->pixels);
	glGenerateMipmap(target);
	return TextureID;
}


JUMA_Texture::JUMA_Texture(std::string filePath, GLenum target, GLenum param, GLenum filtering, GLenum SOILLoadtype, GLenum GLloadType)
{
	
	printf("loading Texture");
	int pos;
	pos = filePath.find(".");
	if (filePath.substr(pos) == ".png") {
		
		IMG_Init(IMG_INIT_PNG);
	}
	else if (filePath.substr(pos) == ".jpg")
		IMG_Init(IMG_INIT_JPG);
	
	SDL_Surface *img = IMG_Load(filePath.c_str());
	id = loadFromSurface(img,target,filtering);
	
	/*printf("Loading texture");

	if (SOILLoadtype == SOIL_LOAD_RGBA || GLloadType == GL_RGBA)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		transparent = true;
	}
	else transparent = false;
	glGenTextures(1, &id);
	glBindTexture(target, id); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	printf(".");
	// Set the texture wrapping parameters
	if (target == GL_TEXTURE_2D)
	{
		glTexParameteri(target, GL_TEXTURE_WRAP_S, filtering);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, filtering);
	}
	// Set texture filtering parameters
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, param);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, param);
	// Load image, create texture and generate mipmaps
	printf(".");
	SDL_Surface *memes = IMG_Load(filePath);
	printf(".");
	glTexImage2D(target, 0, GLloadType, width, height, 0, GLloadType, GL_UNSIGNED_BYTE, image);
	printf(".");
	if (image == NULL) {
		printf("\nERR:Loading failed. Abort");
	}
	else {
		glGenerateMipmap(target);
		printf(".");
		if (SOILLoadtype == SOIL_LOAD_RGBA || GLloadType == GL_RGBA)
		{
			glDisable(GL_BLEND);
		}
		SOIL_free_image_data(image);
		printf(".");
		glBindTexture(target, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		printf("done\n");
	}*/
}

int JUMA_Texture::use(GLenum Channel) {
	glActiveTexture(Channel);	// Activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, id);

	if (transparent)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	return 1;
}

int JUMA_Texture::load(const char* filePath, GLenum target, GLenum param, GLenum filtering, GLenum SOILLoadtype, GLenum GLloadType) {
	printf("Loading texture");

	if (SOILLoadtype == SOIL_LOAD_RGBA || GLloadType == GL_RGBA)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		transparent = true;
	}
	else transparent = false;
	glGenTextures(1, &id);
	glBindTexture(target, id); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	printf(".");
	// Set the texture wrapping parameters
	if (target == GL_TEXTURE_2D)
	{
		glTexParameteri(target, GL_TEXTURE_WRAP_S, param);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, param);
	}
	// Set texture filtering parameters
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	printf(".");
	unsigned char* image = SOIL_load_image(filePath, &width, &height, 0, SOILLoadtype);
	printf(".");
	glTexImage2D(target, 0, GLloadType, width, height, 0, GLloadType, GL_UNSIGNED_BYTE, image);
	printf(".");
	glGenerateMipmap(target);
	printf(".");
	if (SOILLoadtype == SOIL_LOAD_RGBA || GLloadType == GL_RGBA)
	{
		glDisable(GL_BLEND);
	}
	SOIL_free_image_data(image);
	printf(".");
	glBindTexture(target, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	printf("done\n");
	return 1;
}