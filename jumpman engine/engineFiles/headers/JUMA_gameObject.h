#pragma once
//____________________INCLUDES_____________________________
#include <JUMA_vertContainer.h>
#include <JUMA_shaders.h>
#include <JUMA_physics.h>
#include <JUMA_shaders.h>
#include <JUMA_materials.h>
#include <JUMA_matrices.h>
#include <JUMA_bitmanipulator.h>
#include <glm/glm.hpp>
#include <string>
#include <GL/glew.h>
#include <glm/gtx/matrix_decompose.hpp>

#define JUMA_GO_RECT 1
#define JUMA_GO_TRI 2

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
	JUMA_material material;
	unsigned int type;

public:
	glm::vec3 rotation = { 0.0,0.0,0.0 };
	glm::vec3 position = { 0.0,0.0,0.0 };
	glm::vec3 scale = { 1.0,1.0,1.0 };
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
	JUMA_GO(const char* filePath, JUMA_material mat, double mass, std::string transMatName) {
		mass = mass;
		matrixCollection.modelName = transMatName;
		printf("unsupported");
		material = mat;
		type = 4;
	}
	void draw(JUMA_Shader shader) {
		shader.Use();
		//std::cout << VAO;
		glBindVertexArray(VAO);
		//passing Data to Shader
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, matrixCollection.modelName.c_str()), 1, GL_FALSE, glm::value_ptr(matrixCollection.model));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, matrixCollection.viewName.c_str()), 1, GL_FALSE, glm::value_ptr(matrixCollection.view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, matrixCollection.projName.c_str()), 1, GL_FALSE, glm::value_ptr(matrixCollection.proj));
		JUMA_passMatToUniforms(shader, material);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
	void setPos(float x, float y, float z) {
		matrixCollection.model = glm::translate(matrixCollection.model, glm::vec3(x-position.x, y-position.y, z-position.z));
		position = glm::vec3(x, y, z);
	}
	void translate(float x, float y, float z) {
		matrixCollection.model = glm::translate(matrixCollection.model, glm::vec3( x, y, z));
		//printf("\nposx :%f,y:%f,z:%f ", position.x, position.y, position.z);
		position += glm::vec3{ x,y,z };
		//glm::mat4 transformation; // your transformation matrix.
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(matrixCollection.model, scale, rotation, translation, skew, perspective);
		printf("\ngot:x:%f y:%f z:%f Expected:x:%f y:%f z:%f", translation.x, translation.y, translation.z,position.x,position.y,position.z);

	}
	void setRot(float x, float y, float z) {
		matrixCollection.model = glm::rotate(matrixCollection.model, x-rotation.x, glm::vec3(1,0,0));
		matrixCollection.model = glm::rotate(matrixCollection.model, y-rotation.y, glm::vec3(0, 1, 0));
		matrixCollection.model = glm::rotate(matrixCollection.model, z-rotation.z, glm::vec3(0, 0, 1));
		rotation = glm::vec3(x, y, z);

	}
	void setRot_slow(float x, float y, float z) {
		matrixCollection.model = glm::rotate_slow(matrixCollection.model, x - rotation.x, glm::vec3(1, 0, 0));
		matrixCollection.model = glm::rotate_slow(matrixCollection.model, y - rotation.y, glm::vec3(0, 1, 0));
		matrixCollection.model = glm::rotate_slow(matrixCollection.model, z - rotation.z, glm::vec3(0, 0, 1));
		rotation = glm::vec3(x, y, z);

	}
	void setScale_texture() {
		if (material.at(0).type == JUMA_MATTEXTURE) {
			int w, h;
			int miplevel = 0;
			material.at(0).value.Texture.use(material.at(0).texChannel);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH,  &w);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
			scale.x =(float) w / 100;
			scale.y = (float)h / 100;
			//printf("\n:::::width %d height %d aspect: %f::::::\n", w, h, 1.0f*((float)w / (float)h));
			matrixCollection.model = glm::scale(matrixCollection.model, glm::vec3(scale.x,scale.y,scale.z));
		}
		}
};




