#include "stdafx.h"
#include <JUMA_materials.h>

JUMA_materialFracture::JUMA_materialFracture(JUMA_Texture *Texture, JUMA_color Solid, char *uniformName, GLenum texchannel) {

	if (Texture == NULL) {
		value.SolidColor = Solid;
		type = JUMA_MATCOLOR;
	}
	else {
		value.Texture = *Texture;
		type = JUMA_MATTEXTURE;
	}
	texChannel = texchannel;
	UniformName = (char*)malloc(sizeof(uniformName)*strlen(uniformName) + 1);
	strcpy(UniformName, uniformName);
}
int JUMA_materialFracture::JUMA_materialFractureGluint(GLuint *Texture, JUMA_color Solid, char *uniformName, GLenum texchannel) {

	if (Texture == NULL) {
		value.SolidColor = Solid;
		type = JUMA_MATCOLOR;
	}
	else {
		value.Texture.id = *Texture;
		value.Texture.transparent = true;
		texChannel = texchannel;
		type = JUMA_MATTEXTURE;
	}
	texChannel = texchannel;
	UniformName = (char*)malloc(sizeof(uniformName)*strlen(uniformName) + 1);
	strcpy(UniformName, uniformName);
	return 1;
}

int JUMA_passMatToUniforms(JUMA_Shader shader, JUMA_material material) {
	for (int i = 0; i < material.size(); i++) {
		if (material.at(i).enabled) {
			if (material.at(i).type == JUMA_MATCOLOR) {
				glUniform4f(glGetUniformLocation(shader.Program, material.at(i).UniformName), material.at(i).value.SolidColor.r, material.at(i).value.SolidColor.g, material.at(i).value.SolidColor.b, material.at(i).value.SolidColor.r);

			}
			else {
				material.at(i).value.Texture.use(material.at(i).texChannel);
				glUniform1i(glGetUniformLocation(shader.Program, material.at(i).UniformName), material.at(i).texChannel - GL_TEXTURE0);
			}
		}
	}
	return MAT_MSG_SUCCESSFUL;
}
