#pragma once
//____________________REFERENCES___________________________

//_____________________DEFINES_____________________________

//____________________INCLUDES_____________________________
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//____________________STRUCTURES___________________________
struct JUMA_Mat3DCollect{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	char modelName[100];
	char viewName[100];
	char projName[100];
};
//___________________PROTOTYPES____________________________
JUMA_Mat3DCollect JUMA_MakeCollection(glm::mat4 model, glm::mat4 view, glm::mat4 proj, char* modelName, char* viewname, char* projName);