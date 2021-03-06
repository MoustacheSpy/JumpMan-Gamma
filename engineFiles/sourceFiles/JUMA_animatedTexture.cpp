
#include <JUMA_animatedTextures.h>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>

inline bool exists_test(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}
JUMA_TexAnimation::JUMA_TexAnimation(std::string filePath, std::string name) {
	std::string filepathCpy = filePath;
	JUMA_Texture temp;
	int i = 0;
	filepathCpy += " (";
	filepathCpy += std::to_string(i);
	filepathCpy += ").png";
	printf("%s ", filepathCpy.c_str());
	if (!exists_test(filepathCpy)) {
		printf("\nERROR LOADING ANIMATED TEXTURE! COULDNT FIND FRAME ROOT. MAKE SHURE IT NAMES ENDS WITH (number) AND THAT YOU DIDNT INCLUDE (number) OR .PNG IN THE FILEPATH\n");

	}
	else {

		while (exists_test(filepathCpy)) {
			temp = JUMA_Texture(filepathCpy.c_str(), GL_TEXTURE_2D, GL_NEAREST);
			animation.push_back(temp);

			filepathCpy = filePath;
			filepathCpy += " (";
			filepathCpy += std::to_string(i);
			filepathCpy += ")";
			printf("%s ", filepathCpy.c_str());
			i++;
		}
	}
}
