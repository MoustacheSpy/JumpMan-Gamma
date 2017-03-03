#pragma once
//____________________REFERENCES___________________________
///Books
	//Opengl SUPERBIBLE

//_____________________DEFINES_____________________________
#define MAT_MSG_ALREADY_ENABLED -1
#define MAT_MSG_ALREADY_DISABLED -2
#define MAT_MSG_SUCCESSFUL 1

//____________________INCLUDES_____________________________
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <JUMA_textures.h>
#include <JUMA_color.h>
#include <JUMA_texCol.h>
#include <JUMA_shaders.h>
//____________________STRUCTURES___________________________

struct JUMA_materialFracture{
	JUMA_texCol value;
	materialType type;
	char* UniformName;
	GLenum texChannel;
	bool enabled=true;
	JUMA_materialFracture() {  };
	JUMA_materialFracture( JUMA_Texture *Texture, JUMA_color Solid, char *uniformName, GLenum texchannel);
	int JUMA_materialFractureGluint(GLuint *Texture, JUMA_color Solid, char *uniformName, GLenum texchannel); //this is the constructor that I want to delete
	int disable() {
		if (!enabled)
			return MAT_MSG_ALREADY_DISABLED;
		else enabled = false;
		return MAT_MSG_SUCCESSFUL;
	};
	int enable(){
		if (enabled)
			return MAT_MSG_ALREADY_ENABLED;
		else enabled = true;
		return MAT_MSG_SUCCESSFUL;
	}
	
};

typedef std::vector<JUMA_materialFracture> JUMA_material;
//___________________PROTOTYPES____________________________
int JUMA_passMatToUniforms(JUMA_Shader shader, JUMA_material material);