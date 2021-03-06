
#include <JUMA_gameObject.h>
#include <JUMA_bitmanipulator.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

JUMA_GO::JUMA_GO(unsigned int TYPE, JUMA_material mat, double mass, std::string transMatName, glm::mat4 view, std::string viewname, glm::mat4 proj, std::string projName) {
	matrixCollection.modelName = transMatName;
	matrixCollection.proj = proj;
	matrixCollection.projName = projName;
	matrixCollection.view = view;
	matrixCollection.viewName = viewname;
//	scale = {1.0,1.0,1.0};
	//transformations = glm::translate(transformations, glm::vec3(0.0f, 0.0f, 0.0f));
	material = mat;
	vertContainer contain;
	//read shapes from flag bitmask
    GLuint VAO,VBO,EBO;
	type = TYPE;
	if (TYPE == JUMA_GO_RECT) {

		//initialize rectangle
		///generate VAO
		glGenBuffers(1, &VAO);
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
		/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);*/
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		std::cout << VAO;
		printf("\n#####JUMA_DEBUG###### GO init as rect");
		///Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	}
	if (TYPE == JUMA_GO_TRI) {

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
	if (TYPE == JUMA_GO_CUBE) {

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(contain.cubeVerts), contain.cubeVerts, GL_STATIC_DRAW);

		// Position attribute
		/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);*/
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0); // Unbind VAO
	}
	EBOs.push_back(EBO);
	VBOs.push_back(VBO);
	VAOs.push_back(VAO);

}
JUMA_GO::JUMA_GO(char *FilePath, JUMA_material mat, double mass, std::string transMatName, glm::mat4 view, std::string viewname, glm::mat4 proj, std::string projName){
    matrixCollection.modelName = transMatName;
	matrixCollection.proj = proj;
	matrixCollection.projName = projName;
	matrixCollection.view = view;
	matrixCollection.viewName = viewname;
//	scale = {1.0,1.0,1.0};
	//transformations = glm::translate(transformations, glm::vec3(0.0f, 0.0f, 0.0f));
	material = mat;
	vertContainer contain;
	//read shapes from flag bitmask
	// Create an instance of the Importer class
      Assimp::Importer importer;
      // And have it read the given file with some example postprocessing
      // Usually - if speed is not the most important aspect for you - you'll
      // propably to request more postprocessing than we do in this example.
      const aiScene* scene = importer.ReadFile( pFile,
            aiProcess_CalcTangentSpace       |
            aiProcess_Triangulate            |
            aiProcess_JoinIdenticalVertices  |
            aiProcess_SortByPType);

      // If the import failed, report it
      if( !scene)
      {
        DoTheErrorLogging( importer.GetErrorString());
        return false;
      }
      // Now we can access the file's contents.
      if(scene->HasMeshes()){
        for(int i=0;i<scene->mNumMeshes;i++){
            aiMesh* mesh = scene->mMeshes[i];
            //initialize rectangle
		///generate VAO
		glGenBuffers(1, &VAO);
		///generate VBO
		glGenBuffers(1, &VBO);
		///generate EBO
		glGenBuffers(1, &EBO);

		//Save Data into buffes
		///Bind VAO
		glBindVertexArray(this->VAO);

		///Bind VBO and BUFFER DATA into it
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->mVertices), mesh->mVertices, GL_STATIC_DRAW);

		///Bind EBO and BUFFER DATA into it
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->mFaces), mesh->mFaces, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
        }
      }
}
JUMA_GO::JUMA_GO(JUMA_LOADTYPE TYPE, JUMA_material mat, double mass, std::string transMatName, glm::mat4 view, std::string viewname, glm::mat4 proj, std::string projName) {
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


}
