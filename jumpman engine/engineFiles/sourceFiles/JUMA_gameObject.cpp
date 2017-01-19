#include "stdafx.h"
#include <JUMA_gameObject.h>
#include <JUMA_bitmanipulator.h>
JUMA_GO::JUMA_GO(unsigned int TYPE, JUMA_material mat, double mass, std::string transMatName, glm::mat4 view, std::string viewname, glm::mat4 proj, std::string projName) {
	matrixCollection.modelName = transMatName;
	matrixCollection.proj = proj;
	matrixCollection.projName = projName;
	matrixCollection.view = view;
	matrixCollection.viewName = viewname;
	//transformations = glm::translate(transformations, glm::vec3(0.0f, 0.0f, 0.0f));
	material = mat;
	vertContainer contain;
	//read shapes from flag bitmask
	
	type = TYPE;
	if (checkBit(TYPE, 0)) {
		
		//initialize rectangle
		///generate VAO
		glGenBuffers(1, &this->VAO);
		///generate VBO 
		glGenBuffers(1, &VBO);
		///generate EBO
		glGenBuffers(1, &EBO);
		
		//Save Data into buffes
		///Bind VAO
		glBindVertexArray(this->VAO);

		///Bind VBO and BUFFER DATA into it
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(contain.rectangleVerts), contain.rectangleVerts, GL_STATIC_DRAW);

		///Bind EBO and BUFFER DATA into it
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(contain.rectangleIndices), contain.rectangleIndices, GL_STATIC_DRAW);

		///Set up VAP ( Vertex Attribute Pointer )
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		std::cout << VAO;
		printf("\n#####JUMA_DEBUG###### GO init as rect");
		///Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
		
	}
	if (checkBit(TYPE, 1)) {

		printf("\n#####JUMA_DEBUG###### GO init as tri");
		//initialize triangle
		///generate VAO
		glGenBuffers(1, &VAO);
		///generate VBO 
		glGenBuffers(1, &VAO);


		//Save Data into buffes
		///Bind VAO
		glBindVertexArray(VAO);

		///Bind VBO and BUFFER DATA into it
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(contain.triangleVerts), contain.triangleVerts, GL_STATIC_DRAW);

		///Set up VAP ( Vertex Attribute Pointer )
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		///Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
		
	}
}