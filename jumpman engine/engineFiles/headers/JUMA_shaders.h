#pragma once
//____________________REFERENCES___________________________
///Internet:
//Making basic shaders and the standart shader class
	//https://learnopengl.com/#!Getting-started/Shaders

//____________________INCLUDES_____________________________
#include "stdafx.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>// Include glew to get all the required OpenGL headers

//____________________CLASSES______________________________
class JUMA_Shader
{
private:
	char Vertexpath[100];
	char Fragpath[100];
public:
	// The program ID
	GLuint Program;

	// Constructor reads and builds the shader
	JUMA_Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// Use the program
	void Use();
	void recompile();

};
