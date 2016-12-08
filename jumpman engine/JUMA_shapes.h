#pragma once
//____________________REFERENCES___________________________
///Internet
//Triangle vertex data and indices
	//

//_____________________VERTEX DATA_________________________
//---------------------2DRECTANGLE-------------------------
GLfloat rectangleVerts[] = {
	1.0f,  1.0f, 0.0f,  // Top Right
	1.0f, -1.0f, 0.0f,  // Bottom Right
	-1.0f, -1.0f, 0.0f,  // Bottom Left
	-1.0f,  1.0f, 0.0f   // Top Left 
};
//---------------------2DTRIANGLE--------------------------
GLfloat triangleVerts[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f
};

//_____________________INDICES_____________________________
//---------------------2DRECTANGLE-------------------------
GLuint rectangleIndices[] = {  // Note that we start from 0!
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
};

//_____________________BUFFERS_____________________________
GLuint triangleVBO, rectangleVBO;
GLuint rectangleEBO;

//_____________________DEFINES_____________________________
#define JUMA_RECTANGLE 0x00000001
#define JUMA_TRIANGLE 0x00000002
#define JUMA_CIRCLE 0x00000004

//____________________INCLUDES_____________________________
#include <glm\glm.hpp>

//___________________PROTOTYPES____________________________
int initShapes(unsigned int FLAGS);
