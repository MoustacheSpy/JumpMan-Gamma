#include "stdafx.h"
#include "JUMA_shapes.h"
#include "JUMA_bitmanipulator.h"
#include "JUMA_vertContainer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
int initShapes(unsigned int FLAGS) {
	//read shapes from flag bitmask
	if (checkBit(FLAGS, 0)) {
		//initialize rectangle
		///generate VAO
		glGenBuffers(1, &rectangleVAO);
		///generate VBO 
		glGenBuffers(1, &rectangleVBO);
		///generate EBO
		glGenBuffers(1, &rectangleEBO);

		//Save Data into buffes
		///Bind VAO
		glBindVertexArray(rectangleVAO);

		///Bind VBO and BUFFER DATA into it
		glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVerts), rectangleVerts, GL_STATIC_DRAW);
		
		///Bind EBO and BUFFER DATA into it
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

		///Set up VAP ( Vertex Attribute Pointer )
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		///Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	}
	return 1;
}

void drawRectangle(JUMA_Shader shader, const char* matName, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz) {
	///Creating and filling transform matrices
	//Creating general transform mat
	glm::mat4 transform;
	//Filling general mat
	

	transform = glm::translate(transform, glm::vec3(x, y, z));
	transform = glm::rotate(transform, rx, glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, rz, glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, ry, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(sx, sy, sz));
	

	shader.Use();
	glBindVertexArray(rectangleVAO);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, matName), 1, GL_FALSE, glm::value_ptr(transform));
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void drawRectangle3D(JUMA_Shader shader, JUMA_Mat3DCollect collection, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz){
	glm::mat4 temp;
	if (collection.model == temp) {
		///Creating and filling transform matrices
		//Creating general transform mat
		
		//Filling general mat


		collection.model = glm::translate(collection.model, glm::vec3(x, y, z));
		collection.model = glm::rotate(collection.model, rx, glm::vec3(1.0f, 0.0f, 0.0f));
		collection.model = glm::rotate(collection.model, rz, glm::vec3(0.0f, 1.0f, 0.0f));
		collection.model = glm::rotate(collection.model, ry, glm::vec3(0.0f, 0.0f, 1.0f));
		collection.model = glm::scale(collection.model, glm::vec3(sx, sy, sz));

	}
	shader.Use();
	glBindVertexArray(rectangleVAO);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.modelName), 1, GL_FALSE, glm::value_ptr(collection.model));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.viewName), 1, GL_FALSE, glm::value_ptr(collection.proj));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.projName), 1, GL_FALSE, glm::value_ptr(collection.view));

	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void freeInitBuffers(unsigned int FLAGS) {
	if (checkBit(FLAGS, 0)) {
		glDeleteVertexArrays(1, &rectangleVAO);
		glDeleteBuffers(1, &rectangleVBO);
		glDeleteBuffers(1, &rectangleEBO);
	}
}