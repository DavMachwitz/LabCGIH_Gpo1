//Práctica 4									Nava Benítez David Emilio
//Fecha de entrega: 5 de marzo 2026				320291599

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Previo4_David_Nava", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	//Projection perspective
	float vertices[] = {
		// Posiciones          // Colores (R, G, B)
		-0.5f, -0.5f,  0.5f,   0.45f, 0.30f, 0.15f, // Front (Base)
		 0.5f, -0.5f,  0.5f,   0.45f, 0.30f, 0.15f,
		 0.5f,  0.5f,  0.5f,   0.45f, 0.30f, 0.15f,
		 0.5f,  0.5f,  0.5f,   0.45f, 0.30f, 0.15f,
		-0.5f,  0.5f,  0.5f,   0.45f, 0.30f, 0.15f,
		-0.5f, -0.5f,  0.5f,   0.45f, 0.30f, 0.15f,

		-0.5f, -0.5f, -0.5f,   0.35f, 0.22f, 0.10f, // Back (Más oscuro)
		 0.5f, -0.5f, -0.5f,   0.35f, 0.22f, 0.10f,
		 0.5f,  0.5f, -0.5f,   0.35f, 0.22f, 0.10f,
		 0.5f,  0.5f, -0.5f,   0.35f, 0.22f, 0.10f,
		-0.5f,  0.5f, -0.5f,   0.35f, 0.22f, 0.10f,
		-0.5f, -0.5f, -0.5f,   0.35f, 0.22f, 0.10f,

		 0.5f, -0.5f,  0.5f,   0.40f, 0.26f, 0.12f, // Right (Sombra lateral)
		 0.5f, -0.5f, -0.5f,   0.40f, 0.26f, 0.12f,
		 0.5f,  0.5f, -0.5f,   0.40f, 0.26f, 0.12f,
		 0.5f,  0.5f, -0.5f,   0.40f, 0.26f, 0.12f,
		 0.5f,  0.5f,  0.5f,   0.40f, 0.26f, 0.12f,
		 0.5f, -0.5f,  0.5f,   0.40f, 0.26f, 0.12f,

		-0.5f,  0.5f,  0.5f,   0.40f, 0.26f, 0.12f, // Left
		-0.5f,  0.5f, -0.5f,   0.40f, 0.26f, 0.12f,
		-0.5f, -0.5f, -0.5f,   0.40f, 0.26f, 0.12f,
		-0.5f, -0.5f, -0.5f,   0.40f, 0.26f, 0.12f,
		-0.5f, -0.5f,  0.5f,   0.40f, 0.26f, 0.12f,
		-0.5f,  0.5f,  0.5f,   0.40f, 0.26f, 0.12f,

		-0.5f, -0.5f, -0.5f,   0.25f, 0.15f, 0.08f, // Bottom (Muy oscuro)
		 0.5f, -0.5f, -0.5f,   0.25f, 0.15f, 0.08f,
		 0.5f, -0.5f,  0.5f,   0.25f, 0.15f, 0.08f,
		 0.5f, -0.5f,  0.5f,   0.25f, 0.15f, 0.08f,
		-0.5f, -0.5f,  0.5f,   0.25f, 0.15f, 0.08f,
		-0.5f, -0.5f, -0.5f,   0.25f, 0.15f, 0.08f,

		-0.5f,  0.5f, -0.5f,   0.55f, 0.40f, 0.25f, // Top (Brillante / Luz)
		 0.5f,  0.5f, -0.5f,   0.55f, 0.40f, 0.25f,
		 0.5f,  0.5f,  0.5f,   0.55f, 0.40f, 0.25f,
		 0.5f,  0.5f,  0.5f,   0.55f, 0.40f, 0.25f,
		-0.5f,  0.5f,  0.5f,   0.55f, 0.40f, 0.25f,
		-0.5f,  0.5f, -0.5f,   0.55f, 0.40f, 0.25f,
	};

	float vertices2[] = {
		-0.5f, -0.5f,  0.5f,   0.20f, 0.45f, 0.15f, // Front
		 0.5f, -0.5f,  0.5f,   0.20f, 0.45f, 0.15f,
		 0.5f,  0.5f,  0.5f,   0.20f, 0.45f, 0.15f,
		 0.5f,  0.5f,  0.5f,   0.20f, 0.45f, 0.15f,
		-0.5f,  0.5f,  0.5f,   0.20f, 0.45f, 0.15f,
		-0.5f, -0.5f,  0.5f,   0.20f, 0.45f, 0.15f,

		-0.5f, -0.5f, -0.5f,   0.15f, 0.35f, 0.10f, // Back (Oscuro)
		 0.5f, -0.5f, -0.5f,   0.15f, 0.35f, 0.10f,
		 0.5f,  0.5f, -0.5f,   0.15f, 0.35f, 0.10f,
		 0.5f,  0.5f, -0.5f,   0.15f, 0.35f, 0.10f,
		-0.5f,  0.5f, -0.5f,   0.15f, 0.35f, 0.10f,
		-0.5f, -0.5f, -0.5f,   0.15f, 0.35f, 0.10f,

		 0.5f, -0.5f,  0.5f,   0.18f, 0.40f, 0.12f, // Right
		 0.5f, -0.5f, -0.5f,   0.18f, 0.40f, 0.12f,
		 0.5f,  0.5f, -0.5f,   0.18f, 0.40f, 0.12f,
		 0.5f,  0.5f, -0.5f,   0.18f, 0.40f, 0.12f,
		 0.5f,  0.5f,  0.5f,   0.18f, 0.40f, 0.12f,
		 0.5f, -0.5f,  0.5f,   0.18f, 0.40f, 0.12f,

		-0.5f,  0.5f,  0.5f,   0.18f, 0.40f, 0.12f, // Left
		-0.5f,  0.5f, -0.5f,   0.18f, 0.40f, 0.12f,
		-0.5f, -0.5f, -0.5f,   0.18f, 0.40f, 0.12f,
		-0.5f, -0.5f, -0.5f,   0.18f, 0.40f, 0.12f,
		-0.5f, -0.5f,  0.5f,   0.18f, 0.40f, 0.12f,
		-0.5f,  0.5f,  0.5f,   0.18f, 0.40f, 0.12f,

		-0.5f, -0.5f, -0.5f,   0.10f, 0.25f, 0.05f, // Bottom (Sombra fuerte)
		 0.5f, -0.5f, -0.5f,   0.10f, 0.25f, 0.05f,
		 0.5f, -0.5f,  0.5f,   0.10f, 0.25f, 0.05f,
		 0.5f, -0.5f,  0.5f,   0.10f, 0.25f, 0.05f,
		-0.5f, -0.5f,  0.5f,   0.10f, 0.25f, 0.05f,
		-0.5f, -0.5f, -0.5f,   0.10f, 0.25f, 0.05f,

		-0.5f,  0.5f, -0.5f,   0.30f, 0.60f, 0.25f, // Top (Luz de arriba)
		 0.5f,  0.5f, -0.5f,   0.30f, 0.60f, 0.25f,
		 0.5f,  0.5f,  0.5f,   0.30f, 0.60f, 0.25f,
		 0.5f,  0.5f,  0.5f,   0.30f, 0.60f, 0.25f,
		-0.5f,  0.5f,  0.5f,   0.30f, 0.60f, 0.25f,
		-0.5f,  0.5f, -0.5f,   0.30f, 0.60f, 0.25f,
	};

	float vertices3[] = {
		// Posiciones          // Colores (Escala de Blancos/Grises)
		-0.5f, -0.5f,  0.5f,   0.95f, 0.95f, 0.95f, // Front (Blanco casi puro)
		 0.5f, -0.5f,  0.5f,   0.95f, 0.95f, 0.95f,
		 0.5f,  0.5f,  0.5f,   0.95f, 0.95f, 0.95f,
		 0.5f,  0.5f,  0.5f,   0.95f, 0.95f, 0.95f,
		-0.5f,  0.5f,  0.5f,   0.95f, 0.95f, 0.95f,
		-0.5f, -0.5f,  0.5f,   0.95f, 0.95f, 0.95f,

		-0.5f, -0.5f, -0.5f,   0.75f, 0.75f, 0.75f, // Back (Gris sombra)
		 0.5f, -0.5f, -0.5f,   0.75f, 0.75f, 0.75f,
		 0.5f,  0.5f, -0.5f,   0.75f, 0.75f, 0.75f,
		 0.5f,  0.5f, -0.5f,   0.75f, 0.75f, 0.75f,
		-0.5f,  0.5f, -0.5f,   0.75f, 0.75f, 0.75f,
		-0.5f, -0.5f, -0.5f,   0.75f, 0.75f, 0.75f,

		 0.5f, -0.5f,  0.5f,   0.85f, 0.85f, 0.85f, // Right (Gris claro)
		 0.5f, -0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
		 0.5f,  0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
		 0.5f,  0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
		 0.5f,  0.5f,  0.5f,   0.85f, 0.85f, 0.85f,
		 0.5f, -0.5f,  0.5f,   0.85f, 0.85f, 0.85f,

		-0.5f,  0.5f,  0.5f,   0.85f, 0.85f, 0.85f, // Left
		-0.5f,  0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
		-0.5f, -0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
		-0.5f, -0.5f, -0.5f,   0.85f, 0.85f, 0.85f,
		-0.5f, -0.5f,  0.5f,   0.85f, 0.85f, 0.85f,
		-0.5f,  0.5f,  0.5f,   0.85f, 0.85f, 0.85f,

		-0.5f, -0.5f, -0.5f,   0.65f, 0.65f, 0.65f, // Bottom (Sombra fuerte)
		 0.5f, -0.5f, -0.5f,   0.65f, 0.65f, 0.65f,
		 0.5f, -0.5f,  0.5f,   0.65f, 0.65f, 0.65f,
		 0.5f, -0.5f,  0.5f,   0.65f, 0.65f, 0.65f,
		-0.5f, -0.5f,  0.5f,   0.65f, 0.65f, 0.65f,
		-0.5f, -0.5f, -0.5f,   0.65f, 0.65f, 0.65f,

		-0.5f,  0.5f, -0.5f,   1.00f, 1.00f, 1.00f, // Top (Blanco puro / Luz cenital)
		 0.5f,  0.5f, -0.5f,   1.00f, 1.00f, 1.00f,
		 0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
		 0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
		-0.5f,  0.5f,  0.5f,   1.00f, 1.00f, 1.00f,
		-0.5f,  0.5f, -0.5f,   1.00f, 1.00f, 1.00f,
	};


	GLuint VBOs[3], VAOs[3];
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	//Cubos cafes
	glBindVertexArray(VAOs[0]);
	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Cubos verdes
	glBindVertexArray(VAOs[1]);
	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	

	//Cubo blanco
	glBindVertexArray(VAOs[2]);
	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		////////////////////////// Cubo blanco ///////////////////////////
		glBindVertexArray(VAOs[2]);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, 0.88f));
		model = glm::scale(model, glm::vec3(2.0f, 0.25f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.88f, -1.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, -0.88f));
		model = glm::scale(model, glm::vec3(2.0f, 0.25f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.88f, -1.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		/////////////////////Cubos cafes ///////////////////////////
		glBindVertexArray(VAOs[0]);
		//Tronco
	    model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 2.0f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Base del árbol
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.25f));
		model = glm::scale(model, glm::vec3(0.5f, 0.4f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.4f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -0.25f));
		model = glm::scale(model, glm::vec3(0.5f, 0.4f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.4f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -0.9f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.2f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, -0.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, -0.9f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.2f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.3f, -0.9f, 0.26f));
		model = glm::scale(model, glm::vec3(0.25f, 0.20f, 0.25f));
		//model = glm::rotate(model, 0.78f, glm::vec3(0.0f, 0.78f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.3f, -0.9f, -0.26f));
		model = glm::scale(model, glm::vec3(0.25f, 0.20f, 0.25f));
		//model = glm::rotate(model, 0.78f, glm::vec3(0.0f, 0.78f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, -0.9f, 0.26f));
		model = glm::scale(model, glm::vec3(0.25f, 0.20f, 0.25f));
		//model = glm::rotate(model, 0.78f, glm::vec3(0.0f, 0.78f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, -0.9f, -0.26f));
		model = glm::scale(model, glm::vec3(0.25f, 0.20f, 0.25f));
		//model = glm::rotate(model, 0.78f, glm::vec3(0.0f, 0.78f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.25f));
		model = glm::scale(model, glm::vec3(0.5f, 0.4f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.4f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, -0.25f));
		model = glm::scale(model, glm::vec3(0.5f, 0.4f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.4f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//////////////////////////////// Cubos verdes ///////////////////////////////
		glBindVertexArray(VAOs[1]);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		////Cruces de hojas laterales

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, 0.86f));
		model = glm::scale(model, glm::vec3(1.0f, 1.5f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.86f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 1.5f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, -0.86f));
		model = glm::scale(model, glm::vec3(1.0f, 1.5f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.86f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 1.5f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, 0.86f));
		model = glm::scale(model, glm::vec3(1.5f, 0.75f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.86f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, -0.86f));
		model = glm::scale(model, glm::vec3(1.5f, 0.75f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.86f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cruces peqeuñas

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, 1.1f));
		model = glm::scale(model, glm::vec3(0.3f, 0.6f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, 1.1f));
		model = glm::scale(model, glm::vec3(0.6f, 0.3f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.1f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.6f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.1f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, -1.1f));
		model = glm::scale(model, glm::vec3(0.3f, 0.6f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, -1.1f));
		model = glm::scale(model, glm::vec3(0.6f, 0.3f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.1f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.6f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.1f, 1.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		///////////////////Parte superior de las hojas/////

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.25f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.25f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.25f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.7f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.25f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/////

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.25f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// Swap the screen buffers
		glBindVertexArray(VAOs[2]);
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAOs[2]);
	glDeleteBuffers(1, &VBOs[2]);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.04f;
 }


