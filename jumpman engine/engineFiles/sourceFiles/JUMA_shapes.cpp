#include "stdafx.h"
#include <JUMA_shapes.h>
#include <JUMA_bitmanipulator.h>
#include <JUMA_vertContainer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
vertContainer cont;
struct  {
	bool squareInit = false;
	bool triangleInit = false;

}initCheckerShapes;
int initShapes(unsigned int FLAGS) {
	
	//read shapes from flag bitmask
	if (checkBit(FLAGS, 0)) {
		//initialize rectangle
		///generate VAO
		glGenBuffers(1, &cont.rectangleVAO);
		///generate VBO 
		glGenBuffers(1, &cont.rectangleVBO);
		///generate EBO
		glGenBuffers(1, &cont.rectangleEBO);

		//Save Data into buffes
		///Bind VAO
		glBindVertexArray(cont.rectangleVAO);

		///Bind VBO and BUFFER DATA into it
		glBindBuffer(GL_ARRAY_BUFFER, cont.rectangleVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cont.rectangleVerts), cont.rectangleVerts, GL_STATIC_DRAW);
		
		///Bind EBO and BUFFER DATA into it
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cont.rectangleEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cont.rectangleIndices), cont.rectangleIndices, GL_STATIC_DRAW);

		///Set up VAP ( Vertex Attribute Pointer )
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		///Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
		initCheckerShapes.squareInit = true;
	}
	if (checkBit(FLAGS, 1)) {
		//initialize triangle
		///generate VAO
		glGenBuffers(1, &cont.triangleVAO);
		///generate VBO 
		glGenBuffers(1, &cont.triangleVAO);
		

		//Save Data into buffes
		///Bind VAO
		glBindVertexArray(cont.triangleVAO);

		///Bind VBO and BUFFER DATA into it
		glBindBuffer(GL_ARRAY_BUFFER, cont.triangleVAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cont.triangleVerts), cont.triangleVerts, GL_STATIC_DRAW);

		///Set up VAP ( Vertex Attribute Pointer )
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		///Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
		initCheckerShapes.triangleInit = true;
	}
	return 1;
}

void drawRectangle(JUMA_Shader shader, const char* matName, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz) {

	bool changedDepth = false;
	if (!glIsEnabled(GL_DEPTH_TEST)) {
		glEnable(GL_DEPTH_TEST);
		changedDepth = true;
	}
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
	glBindVertexArray(cont.rectangleVAO);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, matName), 1, GL_FALSE, glm::value_ptr(transform));
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	if (changedDepth == true)
		glDisable(GL_DEPTH_TEST);
}

void drawTriangle(JUMA_Shader shader, const char* matName, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz) {

	bool changedDepth = false;
	if (!glIsEnabled(GL_DEPTH_TEST)) {
		glEnable(GL_DEPTH_TEST);
		changedDepth = true;
	}
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
	glBindVertexArray(cont.triangleVAO);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, matName), 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	if (changedDepth == true)
		glDisable(GL_DEPTH_TEST);
}


void drawTriangle3D(JUMA_Shader shader, JUMA_Mat3DCollect collection, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz) {

	bool changedDepth = false;
	if (!glIsEnabled(GL_DEPTH_TEST)) {
		glEnable(GL_DEPTH_TEST);
		changedDepth = true;
	}
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
	glBindVertexArray(cont.triangleVAO);
	
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.modelName), 1, GL_FALSE, glm::value_ptr(collection.model));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.viewName), 1, GL_FALSE, glm::value_ptr(collection.proj));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.projName), 1, GL_FALSE, glm::value_ptr(collection.view));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	if (changedDepth == true)
		glDisable(GL_DEPTH_TEST);
}

void drawRectangle3D(JUMA_Shader shader, JUMA_material material, JUMA_Mat3DCollect collection, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz){

	bool changedDepth = false;
	if (!glIsEnabled(GL_DEPTH_TEST)) {
		glEnable(GL_DEPTH_TEST);
		changedDepth = true;
	}
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
	//passing Material to shader
	JUMA_passMatToUniforms(shader, material);
	glBindVertexArray(cont.rectangleVAO);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.modelName), 1, GL_FALSE, glm::value_ptr(collection.model));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.viewName), 1, GL_FALSE, glm::value_ptr(collection.proj));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, collection.projName), 1, GL_FALSE, glm::value_ptr(collection.view));

	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	if (changedDepth == true)
		glDisable(GL_DEPTH_TEST);
}

void freeInitBuffers(unsigned int FLAGS) {
	if (checkBit(FLAGS, 0)) {
		glDeleteVertexArrays(1, &cont.rectangleVAO);
		glDeleteBuffers(1, &cont.rectangleVBO);
		glDeleteBuffers(1, &cont.rectangleEBO);
	}
}