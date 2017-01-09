#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
//_____________________VERTEX DATA_________________________
//---------------------2DRECTANGLE-------------------------

struct vertContainer {
	GLfloat rectangleVerts[20] = {
		1.0f,  1.0f, 0.0f, 1.0f,1.0f, // Top Right
		1.0f, -1.0f, 0.0f,  1.0f,0.0f,// Bottom Right
		-1.0f, -1.0f, 0.0f, 0.0f,0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,  0.0f,1.0f // Top Left 
	};
	//---------------------2DTRIANGLE--------------------------
	GLfloat triangleVerts[12] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f
	};

	//_____________________INDICES_____________________________
	//---------------------2DRECTANGLE-------------------------
	GLuint rectangleIndices[6] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};
	GLuint triangleVBO, rectangleVBO;
	GLuint rectangleVAO, triangleVAO;
	GLuint rectangleEBO;
};
//_____________________BUFFERS_____________________________


