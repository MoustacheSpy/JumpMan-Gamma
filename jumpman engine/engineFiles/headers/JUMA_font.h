#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <JUMA_textures.h>
#include <GL\glew.h>
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
	JUMA_Texture makeTexture();
	void draw(JUMA_Shader shader,glm::mat4 view,glm::mat4 proj,float x,float y,float z)
	{
		initShapes(JUMA_RECTANGLE);
		
		JUMA_Mat3DCollect collect;
		collect.view = view;
		collect.proj = proj;
		strcpy(collect.modelName, "model");
		strcpy(collect.viewName, "view");
		strcpy(collect.projName, "projection");


		drawRectangle3D(shader, mat, collect,x,y,z,0.0,0.0,0.0,1.0,1.0,1.0);
	}
	JUMA_Texture convertToTexture() {
		JUMA_Texture _this;
		_this.id = _this.loadFromSurface(sourceSurface,GL_TEXTURE_2D,GL_NEAREST);
		return _this;
	}
	/*void draw(vertContainer cont,float x, float y) {
		glm::mat4 model;
		glActiveTexture(GL_TEXTURE0);	// Activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		model = glm::translate(model, glm::vec3(x, y, 0.0));

		glUniform1i(glGetUniformLocation(text.Program, "ourTexture;"), GL_TEXTURE0);
		glBindVertexArray(cont.rectangleVAO);
		glUniformMatrix4fv(glGetUniformLocation(text.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}*/
};