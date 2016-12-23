#pragma once
//____________________REFERENCES___________________________

//_____________________DEFINES_____________________________

//____________________INCLUDES_____________________________
#include "JUMA_textures.h"
#include <vector>

//____________________STRUCTURES___________________________

//____________________CLASS________________________________
class JUMA_TexAnimation {
private:
	std::vector<JUMA_Texture> animation;
	char name[100];
public:
	JUMA_TexAnimation() { };
	JUMA_TexAnimation(std::string filePath, std::string name);
};

//___________________PROTOTYPES____________________________
