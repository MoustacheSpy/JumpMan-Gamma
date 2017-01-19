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
	GLuint VBO,VAO,EBO;
	JUMA_Mat3DCollectPlus matrixCollection;
	JUMA_material material;
	unsigned int type;

public:
	glm::vec3 position = { 0.0,0.0,0.0 };
	JUMA_GO() {
		velocity = { 0.0,0.0,0.0 };
		mass = 0;
		VBO = 0;
		EBO = 0;
		VAO = 0;
		type = 0;
		matrixCollection.modelName = std::string("UNDEFINED");
	};
	JUMA_GO(unsigned int TYPE, JUMA_material mat, double mass, std::string transMatName, glm::mat4 view, std::string viewname,glm::mat4 proj,std::string projName);
	JUMA_GO(const char* filePath, JUMA_material mat, double mass, std::string transMatName) {
		mass = mass;
		matrixCollection.modelName = transMatName;
		printf("unsupported");
		material = mat;
		type = 4;
	}
	void draw(JUMA_Shader shader) {
		shader.Use();
		std::cout << VAO;
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
		matrixCollection.model = glm::translate(matrixCollection.model, glm::vec3(x, y, z));
		position = glm::vec3(x, y, z);
	}
	void translate(float x, float y, float z) {
		matrixCollection.model = glm::translate(matrixCollection.model, glm::vec3(position.x += x, position.y += y, position.z += z));
	}
};





