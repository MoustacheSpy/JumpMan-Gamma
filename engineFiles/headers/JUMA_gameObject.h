#pragma once
//____________________INCLUDES_____________________________
#include <JUMA_vertContainer.h>
#include <JUMA_shaders.h>
#include <JUMA_physics.h>
#include <JUMA_shaders.h>
#include <JUMA_materials.h>
#include <JUMA_matrices.h>
#include <JUMA_bitmanipulator.h>
#include <JUMA_transform.h>
#include <glm/glm.hpp>
#include <string>
#include <GL/glew.h>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#define JUMA_GO_RECT 1
#define JUMA_GO_TRI 2
#define JUMA_GO_CUBE 3

typedef enum{JUMA_GO_MODEL}JUMA_LOADTYPE;
/*
//NOTE TO READER: NOT USING VERT CONTAINER BECAUSE OF "ALREADY DEFINED" ERROR EVENTHOUGH THERE ARE NO DOUBLE INCLUSIONS AND EVERYTHING IS PROTECTED
//_____________________VERTEX DATA_________________________
//---------------------2DRECTANGLE-------------------------
GLfloat rectVerts[] = {
1.0f,  1.0f, 0.0f, 1.0f,1.0f, // Top Right
1.0f, -1.0f, 0.0f,  1.0f,0.0f,// Bottom Right
-1.0f, -1.0f, 0.0f, 0.0f,0.0f, // Bottom Left
-1.0f,  1.0f, 0.0f,  0.0f,1.0f // Top Left
};
//---------------------2DTRIANGLE--------------------------
GLfloat triVerts[] = {
-1.0f, -1.0f, 0.0f,
1.0f, -1.0f, 0.0f,
0.0f,  1.0f, 0.0f
};

//_____________________INDICES_____________________________
//---------------------2DRECTANGLE-------------------------
GLuint rectIndices[] = {  // Note that we start from 0!
0, 1, 3,   // First Triangle
1, 2, 3    // Second Triangle
};

*/
//____________________CLASS________________________________


class JUMA_GO {
private:

	glm::vec3 velocity;
	float mass;
	GLuint VBO, VAO, EBO;
	JUMA_Mat3DCollectPlus matrixCollection;

	unsigned int type;

public:
    JUMA_Transform transform;
	JUMA_material material;
	JUMA_GO() {
		velocity = { 0.0,0.0,0.0 };
		mass = 0;
		VBO = 0;
		EBO = 0;
		VAO = 0;
		type = 0;
		matrixCollection.modelName = std::string("UNDEFINED");
	};
	JUMA_GO(unsigned int TYPE, JUMA_material mat, double mass, std::string transMatName, glm::mat4 view, std::string viewname, glm::mat4 proj, std::string projName);
	JUMA_GO(JUMA_LOADTYPE TYPE, JUMA_material mat, double mass, std::string transMatName, glm::mat4 view, std::string viewname, glm::mat4 proj, std::string projName);

	JUMA_GO(const char* filePath, JUMA_material mat, double mass, std::string transMatName) {
		mass = mass;
		matrixCollection.modelName = transMatName;
		printf("unsupported");
		material = mat;
		type = 4;
	}
	void draw(JUMA_Shader shader) {
		//std::cout << VAO;
        matrixCollection.model = transform.getMat();
		glBindVertexArray(VAO);
		//passing Data to Shader
		shader.Use();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, matrixCollection.modelName.c_str()), 1, GL_FALSE, glm::value_ptr(matrixCollection.model));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, matrixCollection.viewName.c_str()), 1, GL_FALSE, glm::value_ptr(matrixCollection.view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, matrixCollection.projName.c_str()), 1, GL_FALSE, glm::value_ptr(matrixCollection.proj));
		JUMA_passMatToUniforms(shader, material);
		if (type == JUMA_GO_CUBE)
			glDrawArrays(GL_TRIANGLES, 0, 36);
		else
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		matrixCollection.model = glm::mat4();
	}
	/*void setScale_texture() {
		if (material.at(0).type == JUMA_MATTEXTURE) {
			int w, h;
			int miplevel = 0;
			material.at(0).value.Texture.use(material.at(0).texChannel);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
			//printf("\n:::::width %d height %d aspect: %f::::::\n", w, h, 1.0f*((float)w / (float)h));
			matrixCollection.model = glm::scale(matrixCollection.model, glm::vec3(scale.x, scale.y, 1.0f));
		}
	}*/
};




