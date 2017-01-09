#pragma once
//____________________INCLUDES_____________________________
#include "JUMA_vertContainer.h"
#include "JUMA_shaders.h"
#include "JUMA_physics.h"
#include "JUMA_shaders.h"
#include "JUMA_materials.h"
#include "JUMA_bitmanipulator.h"
#include <glm/glm.hpp>
#include <string>
#include <GL/glew.h>
/*
//NOTE TO READER: NOT USING VERT CONTAINER BECAUSE OF "ALREADY DEFINED" ERROR EVENTHOUGH THERE ARE NO DOUBLE INCLUSIONS AND EVERYTHING IS PROTECTED
//_____________________VERTEX DATA_________________________
//---------------------2DRECTANGLE-------------------------
GLfloat rectVerts[] = {
	1.0f,  1.0f, 0.0f, 1.0f,1.0f, // Top Right
	1.0f, -1.0f, 0.0f,  1.0f,0.0f,// Bottom Right
	-1.0f, -1.0f, 0.0f, 0.0f,0.0f, // Bottom Left
	-1.0f,  1.0f, 0.0f,  0.0f,1.0f // Top Left 
};
//---------------------2DTRIANGLE--------------------------
GLfloat triVerts[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f
};

//_____________________INDICES_____________________________
//---------------------2DRECTANGLE-------------------------
GLuint rectIndices[] = {  // Note that we start from 0!
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
};

*/
//____________________CLASS________________________________
class JUMA_GO {
private:
	d3Vec velocity;
	float mass;
	GLuint VBO,VAO,EBO;
	glm::mat4 transformations;
	std::string transMatName;
	JUMA_material material;
	unsigned int type;

public:
	JUMA_GO() {
		velocity = { 0.0,0.0,0.0 };
		mass = 0;
		VBO = 0;
		EBO = 0;
		VAO = 0;
		type = 0;
		transMatName = "UNDEFINED";
	};
	JUMA_GO(unsigned int TYPE, double mass, std::string transMat);
	JUMA_GO(const char* filePath,double mass, std::string transMat) {
		mass = mass;
		transMatName = transMat;
		printf("unsupported");
		type = 4;
	}
	void draw(JUMA_Shader shader) {
		shader.Use();
		glBindVertexArray(VAO);
		//passing transformation Matrix to Shader
		JUMA_passMatToUniforms(shader, material);
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, transMatName.c_str()), 1, GL_FALSE, glm::value_ptr(transformations));
		if (checkBit(type, 1)) {
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}else
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};





