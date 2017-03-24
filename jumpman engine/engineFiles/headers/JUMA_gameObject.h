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
struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 uv;
};

class JUMA_Mesh {
private:
	GLuint VAO, VBO, EBO;

	void initMesh() {
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
			&this->vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
			&this->indices[0], GL_STATIC_DRAW);

		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid*)0);
		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid*)offsetof(Vertex, normal));
		// Vertex Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<JUMA_Texture> textures;

	JUMA_Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<JUMA_Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		this->initMesh();
	}
	void draw(JUMA_Shader shader) {
		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		for (GLuint i = 0; i < this->textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
											  // Retrieve texture number (the N in diffuse_textureN)
			std::stringstream ss;
			std::string number;
			std::string name = this->textures[i].type;
			if (name == "texture_diffuse")
				ss << diffuseNr++; // Transfer GLuint to stream
			else if (name == "texture_specular")
				ss << specularNr++; // Transfer GLuint to stream
			number = ss.str();

			glUniform1f(glGetUniformLocation(shader.Program, ("material." + name + number).c_str()), i);
			glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		// Draw mesh
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

};



class JUMA_Model
{
public:
	/*  Functions   */
	JUMA_Model(GLchar* path)
	{
		if(std::ifstream(path))
			this->loadModel(path);
		else printf("ERROR @ MODEL LOADING::Model does not exist.Aborting...\n");
	}
	JUMA_Model() {};
	void Draw(JUMA_Shader shader) {
		for (GLuint i = 0; i < this->meshes.size(); i++)
			this->meshes[i].draw(shader);
	}
private:
	/*  Model Data  */
	std::vector<JUMA_Mesh> meshes;
	std::string directory;
	std::vector<JUMA_Texture> textures_loaded;
	/*  Functions   */
	void loadModel(std::string path) {
		// Read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString();
			return;
		}
		// Retrieve the directory path of the filepath
		this->directory = path.substr(0, path.find_last_of('/'));

		// Process ASSIMP's root node recursively
		this->processNode(scene->mRootNode, scene);
	}
	void processNode(aiNode* node, const aiScene* scene) {
		// Process each mesh located at the current node
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			// The node object only contains indices to index the actual objects in the scene. 
			// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->processMesh(mesh, scene));
		}
		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}
	}
	JUMA_Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
		// Data to fill
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<JUMA_Texture> textures;

		// Walk through each of the mesh's vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
							  // Positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.pos = vector;
			// Normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.uv = vec;
			}
			else
				vertex.uv = glm::vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}
		// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// Retrieve all indices of the face and store them in the indices vector
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		// Process materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
			// Same applies to other texture as the following list summarizes:
			// Diffuse: texture_diffuseN
			// Specular: texture_specularN
			// Normal: texture_normalN

			// 1. Diffuse maps
			std::vector<JUMA_Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. Specular maps
			std::vector<JUMA_Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		// Return a mesh object created from the extracted mesh data
		return JUMA_Mesh(vertices, indices, textures);
	}

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	std::vector<JUMA_Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<JUMA_Texture> textures;
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			GLboolean skip = false;
			for (GLuint j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
					break;
				}
			}
			if (!skip)
			{   // If texture hasn't been loaded already, load it
				printf("texturepath: %s\n", str.C_Str());
				JUMA_Texture texture(str.C_Str(),GL_TEXTURE_2D,GL_LINEAR);
				
				textures.push_back(texture);
				this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
			}
		}
		return textures;
	
	}
};

class JUMA_GO {
private:

	glm::vec3 velocity;
	float mass;
	GLuint VBO, VAO, EBO;
	JUMA_Mat3DCollectPlus matrixCollection;

	unsigned int type;

public:
	glm::vec3 rotation = { 0.0,0.0,0.0 };
	glm::vec3 position = { 0.0,0.0,0.0 };
	glm::vec3 scale = { 1.0,1.0,1.0 };
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
	}
	void setPos(float x, float y, float z) {
		matrixCollection.model = glm::translate(matrixCollection.model, glm::vec3(x - position.x, y - position.y, z - position.z));
		position = glm::vec3(x, y, z);
	}
	void translate(float x, float y, float z) {
		matrixCollection.model = glm::translate(matrixCollection.model, glm::vec3(x, y, z));
		//printf("\nposx :%f,y:%f,z:%f ", position.x, position.y, position.z);
		position += glm::vec3{ x,y,z };
		//glm::mat4 transformation; // your transformation matrix.
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(matrixCollection.model, scale, rotation, translation, skew, perspective);
		printf("\ngot:x:%f y:%f z:%f Expected:x:%f y:%f z:%f", translation.x, translation.y, translation.z, position.x, position.y, position.z);

	}
	void setRot(float x, float y, float z) {
		matrixCollection.model = glm::rotate(matrixCollection.model, x - rotation.x, glm::vec3(1, 0, 0));
		matrixCollection.model = glm::rotate(matrixCollection.model, y - rotation.y, glm::vec3(0, 1, 0));
		matrixCollection.model = glm::rotate(matrixCollection.model, z - rotation.z, glm::vec3(0, 0, 1));
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
			glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
			scale.x = ((float)w / 600.0)*-1;
			scale.y = ((float)h / 600.0);
			//printf("\n:::::width %d height %d aspect: %f::::::\n", w, h, 1.0f*((float)w / (float)h));
			matrixCollection.model = glm::scale(matrixCollection.model, glm::vec3(scale.x, scale.y, scale.z));
		}
	}
};




