#include "stdafx.h"
#include <JUMA_vertContainer.h>
//_____________________VERTEX DATA_________________________
//---------------------2DRECTANGLE-------------------------
GLfloat rectangleVerts[] = {
	1.0f,  1.0f, 0.0f, 1.0f,1.0f, // Top Right
	1.0f, -1.0f, 0.0f,  1.0f,0.0f,// Bottom Right
	-1.0f, -1.0f, 0.0f, 0.0f,0.0f, // Bottom Left
	-1.0f,  1.0f, 0.0f,  0.0f,1.0f // Top Left 
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
