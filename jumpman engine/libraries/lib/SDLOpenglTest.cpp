// OpenGL headers
//#define GLEW_STATIC
#include "stdafx.h"
#include <GL/glew.h>
#include <vector>
#include <SOIL.h>
#include <iostream>
#include <SDL.h>
#include "Shaders.h"

#include "glm/glm.hpp"
#include "GLTextures.h"
#include "camera.h"
#include <ctime>
#include "Model.h"
#define HEIGHT 600
#define WIDTH 600

using namespace std;
GLuint loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_AUTO);
		printf("reach");
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
		);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}
int compileShaderWMessages(GLuint id)
{
	glCompileShader(id);
	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	return 1;
}
int generateAndBindBuffer(GLuint *Bufferidx, int mode, int usage)
{
	glGenBuffers(1, Bufferidx);
	glBindBuffer(mode, *Bufferidx);
	return 1;
}


int main(int argc, char* args[])
{


	SDL_Window *window;
	SDL_Renderer *renderer;
	window = SDL_CreateWindow("ok", 100, 100, HEIGHT, WIDTH, SDL_WINDOW_OPENGL);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		// GLEW failed!
		printf("GLEW INIT FAILED!");
	}

	// _________ Shader Creation __________
	//SHADER COLLECTION

	Shader colorShade("./shaders/colorTest/colorTest.vs", "./shaders/colorTest/colorTest.frag");
	Shader textureHandel("./shaders/textureBasic/textureBasic.vs", "./shaders/textureBasic/textureBasic.frag");
	Shader lampShader("./shaders/lampShader/lampShader.vs", "./shaders/lampShader/lampShader.frag");
	Shader lightingShader("./shaders/lightingBasic/lightingBasic.vs", "./shaders/lightingBasic/lightingBasic.frag");
	Shader skybox("./shaders/skyboxBasic/skyboxBasic.vs", "./shaders/skyboxBasic/skyboxBasic.frag");
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f,  -8.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.1f,  1.5f, -1.0f)
	};

	GLuint indices[] =    // Note that we start from 0!
	{
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	GLTexture container("./images/container2.png", GL_TEXTURE_2D, GL_NEAREST, GL_LINEAR_MIPMAP_LINEAR, SOIL_LOAD_AUTO, GL_RGBA);
	GLTexture container_spec("./images/container2_specular.png", GL_TEXTURE_2D, GL_NEAREST, GL_LINEAR_MIPMAP_LINEAR, SOIL_LOAD_AUTO, GL_RGBA);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); // Unbind VAO


						  // Load and create a texture


						  // Create transformations

						  // Get their uniform location
	GLint modelLoc = glGetUniformLocation(textureHandel.Program, "model");
	GLint viewLoc = glGetUniformLocation(textureHandel.Program, "view");
	GLint projLoc = glGetUniformLocation(textureHandel.Program, "projection");
	glEnable(GL_DEPTH_TEST);
	Camera cam1;
	//Add a lamp

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glm::vec3 lightPos(1.2f, 1.0f, -4.0f);

	// Setup skybox VAO
	GLuint skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
	vector<const GLchar*> faces;
	faces.push_back("./images/violentdays_rt.jpg");
	faces.push_back("./images/violentdays_lf.jpg");
	faces.push_back("./images/violentdays_up.jpg");
	faces.push_back("./images/violentdays_dn.jpg");
	faces.push_back("./images/violentdays_bk.jpg");
	faces.push_back("./images/violentdays_ft.jpg");
	GLuint cubemapTexture = loadCubemap(faces);
	Model nanosuit("C:/Users/MoustacheSpy/Desktop/container/nanosuit/nanosuit.obj");
	Model lens("C:/Users/MoustacheSpy/Desktop/container/lens.dae");
	Model level("C:/Users/MoustacheSpy/Desktop/testLevel.3ds");
	while (1)
	{

		// Draw skybox first




		glClearColor(0.2, 0.2, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthMask(GL_TRUE);// Remember to turn depth writing off

		container.use(GL_TEXTURE0);
		container_spec.use(GL_TEXTURE1);
		lightingShader.Use();
		glBindVertexArray(VAO);
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		clock_t start = clock();
		lightPos=cam1.cameraPos;
		lightPos.y += 0.5;
		/*
		if (keystate[SDL_SCANCODE_UP])
		{
			lightPos.z += 0.005*(clock()/CLOCKS_PER_SEC);
		}
		if (keystate[SDL_SCANCODE_DOWN])
		{
			lightPos.z -= 0.005*(clock() / CLOCKS_PER_SEC);
		}
		if (keystate[SDL_SCANCODE_LEFT])
		{
			lightPos.x += 0.005*(clock() / CLOCKS_PER_SEC);
		}
		if (keystate[SDL_SCANCODE_RIGHT])
		{
			lightPos.x -= 0.005*(clock() / CLOCKS_PER_SEC);
		}*/
		GLint matSpecularLoc = glGetUniformLocation(lightingShader.Program, "material.specular");
		GLint matShineLoc = glGetUniformLocation(lightingShader.Program, "material.shininess");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");
		GLint lightAmbientLoc = glGetUniformLocation(lightingShader.Program, "light.ambient");
		GLint lightDiffuseLoc = glGetUniformLocation(lightingShader.Program, "light.diffuse");
		GLint lightSpecularLoc = glGetUniformLocation(lightingShader.Program, "light.specular");
		GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");

		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "light.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "light.linear"), 0.09);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "light.quadratic"), 0.032);
		glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
		glUniform3f(lightDiffuseLoc, 1.0f, 1.0f, 1.0f); // Let's darken the light a bit to fit the scene
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(matSpecularLoc, 0.2f, 0.2f, 0.2f);
		glUniform1f(matShineLoc, 999.0f);
		glUniform3f(viewPosLoc, cam1.cameraPos.x, cam1.cameraPos.y, cam1.cameraPos.z);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);


		glDepthMask(GL_TRUE);
		// ... Draw rest of the scene
		cam1.processKeyboard();
		cam1.processMouse_FPS();


		// Create camera transformations

		glm::mat4 view = glm::lookAt(cam1.cameraPos, cam1.cameraPos + cam1.cameraFront, cam1.cameraUp);
		glm::mat4 projection = glm::perspective(cam1.fov, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");
		glm::mat4 model;

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		
		for (GLuint i = 0; i < 10; i++)
		{
			//Shading Setup
			glm::mat4 temp;
			model = temp;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			if (i % 3 == 0)
				angle = (float)clock() / CLOCKS_PER_SEC;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 1.0f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glm::mat4 temp;
		model = temp;
		model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 1.0f, 0.5f));
		model = glm::scale(model, glm::vec3(20.2f));
		glBindVertexArray(0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		lens.Draw(lightingShader);
		
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -0.2f));
		model = glm::scale(model, glm::vec3(0.03f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		nanosuit.Draw(lightingShader);
		model = glm::scale(model, glm::vec3(1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		level.Draw(lightingShader);
		
		lampShader.Use();
		glUniform1i(glGetUniformLocation(skybox.Program, "skybox"), 0);

		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		skybox.Use();
		view = glm::mat4(glm::mat3(glm::lookAt(cam1.cameraPos, cam1.cameraPos + cam1.cameraFront, cam1.cameraUp)));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(skybox.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skybox.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		// skybox cube
		/*glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(skybox.Program, "skybox"), 10);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default*/
		SDL_GL_SwapWindow(window);

		while (((clock() - start) * 1000 / CLOCKS_PER_SEC) <16)
			;

		float MS = (float)((clock() - start) * 1000 / CLOCKS_PER_SEC);
		// Time in seconds
		float S;
		cam1.frameTime = S = MS / 1000.0f;
		// Frames per seconds
		float FPS = 1000.0f / MS;
		//printf("%f \n",FPS);
		//    printf( "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	}
	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
	SDL_GL_DeleteContext(glcontext);
	return 0;
}
