//Práctica 2						Nava Benítez David Emilio
//20/02/2025						320291599

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica2_David_Nava", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		-0.02f,  0.87f, 0.0f,    1.0f,1.0f,1.0f,  // V0
		-0.06f, 0.84f, 0.0f,    1.0f,1.0f,1.0f,  // V1
		0.0f, 0.8f, 0.0f,   1.0f,1.0f,1.0f,  //V2
		-0.07f,  0.83f, 0.0f,   1.0f,1.0f,1.0f, //V3
		-0.1f,  0.87f, 0.0f,   1.0f,1.0f,1.0f, //V4
		-0.11f,  0.82f, 0.0f,   1.0f,1.0f,1.0f, //V5
		-0.08f,  0.81f, 0.0f,   1.0f,1.0f,1.0f, //V6
		-0.1f,  0.78f, 0.0f,   1.0f,1.0f,1.0f, //V7
		-0.08f,  0.79f, 0.0f,   1.0f,1.0f,1.0f, //V8
		-0.07f,  0.76f, 0.0f,   1.0f,1.0f,1.0f, //V9
		-0.17f,  0.65f, 0.0f,   1.0f,1.0f,1.0f, //V10
		-0.11f,  0.68f, 0.0f,   1.0f,1.0f,1.0f, //V11
		-0.05f,  0.68f, 0.0f,   1.0f,1.0f,1.0f, //V12
		-0.01f,  0.72f, 0.0f,   1.0f,1.0f,1.0f, //V13
		-0.01f,  0.76f, 0.0f,   1.0f,1.0f,1.0f, //V14
		0.12f,  0.7f, 0.0f,   1.0f,1.0f,1.0f, //V15
		0.09f,  0.68f, 0.0f,   1.0f,1.0f,1.0f, //V16
		0.04f,  0.67f, 0.0f,   1.0f,1.0f,1.0f, //V17
		-0.13f,  0.63f, 0.0f,   1.0f,1.0f,1.0f, //V18
		-0.1f,  0.61f, 0.0f,   1.0f,1.0f,1.0f, //V19
		-0.18f,  0.59f, 0.0f,   1.0f,1.0f,1.0f, //V20
		-0.13f,  0.6f, 0.0f,   1.0f,1.0f,1.0f, //V21
		-0.25f,  0.54f, 0.0f,   1.0f,1.0f,1.0f, //V22
		-0.23f,  0.53f, 0.0f,   1.0f,1.0f,1.0f, //V23
		-0.27f,  0.53f, 0.0f,   1.0f,1.0f,1.0f, //V24
		-0.27f,  0.49f, 0.0f,   1.0f,1.0f,1.0f, //V25
		-0.23f,  0.49f, 0.0f,   1.0f,1.0f,1.0f, //V26
		-0.2f,  0.44f, 0.0f,   1.0f,1.0f,1.0f, //V27
		-0.18f,  0.49f, 0.0f,   1.0f,1.0f,1.0f, //V28
		-0.11f,  0.46f, 0.0f,   1.0f,1.0f,1.0f, //V29
		-0.11f,  0.53f, 0.0f,   1.0f,1.0f,1.0f, //V30
		-0.03f,  0.59f, 0.0f,   1.0f,1.0f,1.0f, //V31
		-0.02f,  0.53f, 0.0f,   1.0f,1.0f,1.0f, //V32
		-0.02f,  0.46f, 0.0f,   1.0f,1.0f,1.0f, //V33
		0.05f,  0.53f, 0.0f,   1.0f,1.0f,1.0f, //V34
		0.07f,  0.61f, 0.0f,   1.0f,1.0f,1.0f, //V35
		0.18f,  0.6f, 0.0f,   1.0f,1.0f,1.0f, //V36
		0.1f,  0.53f, 0.0f,   1.0f,1.0f,1.0f, //V37
		0.21f,  0.53f, 0.0f,   1.0f,1.0f,1.0f, //V38
		0.19f,  0.51f, 0.0f,   1.0f,1.0f,1.0f, //V39
		0.2f,  0.4f, 0.0f,   1.0f,1.0f,1.0f, //V40
		0.18f,  0.4f, 0.0f,   1.0f,1.0f,1.0f, //V41
		0.13f,  0.4f, 0.0f,   1.0f,1.0f,1.0f, //V42
		0.08f,  0.44f, 0.0f,   1.0f,1.0f,1.0f, //V43
		0.17f,  0.21f, 0.0f,   1.0f,1.0f,1.0f, //V44
		0.15f,  0.25f, 0.0f,   1.0f,1.0f,1.0f, //V45
		0.0f,  0.4f, 0.0f,   1.0f,1.0f,1.0f, //V46
		-0.05f,  0.39f, 0.0f,   1.0f,1.0f,1.0f, //V47
		-0.01f,  0.36f, 0.0f,   1.0f,1.0f,1.0f, //V48
		-0.02f,  0.37f, 0.0f,   1.0f,1.0f,1.0f, //V49
		-0.05f,  0.32f, 0.0f,   1.0f,1.0f,1.0f, //V50
		0.06f,  0.31f, 0.0f,   1.0f,1.0f,1.0f, //V51
		-0.1f,  0.27f, 0.0f,   1.0f,1.0f,1.0f, //V52
		-0.13f,  0.09f, 0.0f,   1.0f,1.0f,1.0f, //V53
		-0.09f,  0.11f, 0.0f,   1.0f,1.0f,1.0f, //V54
		-0.07f,  0.22f, 0.0f,   1.0f,1.0f,1.0f, //V55
		-0.01f,  -0.02f, 0.0f,   1.0f,1.0f,1.0f, //V56
		0.04f,  0.19f, 0.0f,   1.0f,1.0f,1.0f, //V57
		0.02f,  -0.02f, 0.0f,   1.0f,1.0f,1.0f, //V58
		0.06f,  -0.1f, 0.0f,   1.0f,1.0f,1.0f, //V59
		0.08f,  0.09f, 0.0f,   1.0f,1.0f,1.0f, //V60
		0.12f,  0.09f, 0.0f,   1.0f,1.0f,1.0f, //V61
	};
	unsigned int indices[] = {  // note that we start from 0!
		0,1,// second Triangle
		0,2,
		1,2,
		1,3,
		3,4,
		4,5,
		3,6,
		5,6,
		5,7,
		7,8,
		6,8,
		8,9,
		9,2,
		9,12,
		7,10,
		7,11,
		10,11,
		11,12,
		2,14,
		12,13,
		12,17,
		13,14,
		14,15,
		14,16,
		16,15,
		13,17,
		16,17,
		10,18,
		18,19,
		18,21,
		19,12,
		19,21,
		10,20,
		20,21,
		20,22,
		22,23,
		20,23,
		22,24,
		22,23,
		24,25,
		25,26,
		26,23,
		26,27,
		26,28,
		28,29,
		27,29,
		28,30,
		30,19,
		29,32,
		30,32,
		19,31,
		31,17,
		31,32,
		29,33,
		33,32,
		31,34,
		33,34,
		34,35,
		16,36,
		16,35,
		35,37,
		37,36,
		36,38,
		36,39,
		38,39,
		37,39,
		37,41,
		39,40,
		40,41,
		41,44,
		41,42,
		42,43,
		43,37,
		42,45,
		44,45,
		43,45,
		34,43,
		33,43,
		33,46,
		46,43,
		29,47,
		47,49,
		49,48,
		48,46,
		47,50,
		50,49,
		48,51,
		51,43,
		51,45,
		50,52,
		52,53,
		53,54,
		54,52,
		54,55,
		50,55,
		54,56,
		56,58,
		55,56,
		55,57,
		56,57,
		58,57,
		58,59,
		59,60,
		50,57,
		48,57,
		51,57,
		60,61,
		57,60,
		51,60,
		61,45,
		60,45,


	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the 
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.Use();
		glBindVertexArray(VAO);

		//Inicio Figura:
		glDrawElements(GL_LINES,222,GL_UNSIGNED_INT, 0);





		//Fin Figura
		// Draw our first triangle
        


        glPointSize(1);
        glDrawArrays(GL_POINTS,0,6);
        
        //glDrawArrays(GL_LINES,0,2);
        
        
        //glDrawArrays(GL_TRIANGLES,33,3);
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}