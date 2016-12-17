#include "stdafx.h"
#include "JUMA_shapes.h"
#include "JUMA_bitmanipulator.h"
#include "JUMA_vertContainer.h"
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleVerts, GL_STATIC_DRAW);
		
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

void drawRectangle(JUMA_Shader shader, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz) {
	shader.Use();
	glBindVertexArray(rectangleVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}