#pragma once

//____________________REFERENCES___________________________
///Internet
//Triangle vertex data and indices
	//https://learnopengl.com/#!Getting-started/Hello-Triangle
//Info about gluints and so forth 
	//https://learnopengl.com/#!Getting-started/Hello-Triangle
//General Theories about drawing triangles and rectangles
	//https://learnopengl.com/#!Getting-started/Hello-Triangle
///Books
	//Opengl superbible
	
//_____________________DEFINES_____________________________
#define JUMA_RECTANGLE 0x00000001
#define JUMA_TRIANGLE 0x00000002
#define JUMA_CIRCLE 0x00000004

//____________________INCLUDES_____________________________
#include <GL/glew.h>
#include "JUMA_shaders.h"
#include "JUMA_matrices.h"
#include "JUMA_materials.h"
//___________________PROTOTYPES____________________________
int initShapes(unsigned int FLAGS);
void drawRectangle(JUMA_Shader shader,const char* modelName, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
void drawRectangle3D(JUMA_Shader shader, JUMA_material material,JUMA_Mat3DCollect collection,float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
void drawTriangle(JUMA_Shader shader, const char* matName, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
void drawTriangle3D(JUMA_Shader shader, JUMA_Mat3DCollect collection, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
