#pragma once
//____________________REFERENCES___________________________

//_____________________DEFINES_____________________________

//____________________INCLUDES_____________________________
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
//____________________STRUCTURES___________________________
struct JUMA_Mat3DCollect {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	char modelName[100];
	char viewName[100];
	char projName[100];
};

struct JUMA_Mat3DCollectPlus {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	std::string modelName;
	std::string viewName;
	std::string projName;
};
//___________________PROTOTYPES____________________________
JUMA_Mat3DCollectPlus JUMA_MakeCollection(glm::mat4 model, glm::mat4 view, glm::mat4 proj, char* modelName, char* viewname, char* projName);