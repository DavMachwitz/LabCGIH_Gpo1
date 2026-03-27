//Previo 7					Nava Benitez David Emilio
//21 de marzo de 2026		320291599 
#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
bool mouseCaptured = false;


// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

							// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Texturizado - Practica7_David_Nava", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);


	// Build and compile our shader program
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
       -0.5f, -0.5f, 0.5f,		1.0f, 1.0f,1.0f,	0.048f,0.22f,				//Front(1)
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.16f,0.22f,
		0.5f,  0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.16f,0.58f,
		0.5f,  0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.16f,0.58f,
		-0.5f,  0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.048f,0.58f,
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.048f,0.22f,
		
	   -0.5f, -0.5f, -0.5f,		1.0f, 1.0f,1.0f,	0.68f,0.18f,				//Back
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.79f,0.18f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.79f,0.53f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.79f,0.53f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,1.0f,    0.69f,0.53f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,1.0f,    0.68f,0.18f,
		
		-0.5f, 0.5f, 0.5f,		1.0f, 1.0f,1.0f,	0.41f,0.13f,				//left (3)
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.49f,0.23f,
		-0.5f,  -0.5f, -0.5f,	1.0f, 1.0f,1.0f,    0.45f,0.56f,
		-0.5f,  -0.5f, -0.5f,	1.0f, 1.0f,1.0f,    0.45f,0.56f,
		-0.5f,  -0.5f, 0.5f,	1.0f, 1.0f,1.0f,    0.36f,0.44f,
		-0.5f, 0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.41f,0.13f,
      
		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,1.0f,	0.59f,0.38f,				//right(4)
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.65f,0.67f,
		0.5f, -0.5f,-0.5f,		1.0f, 1.0f,1.0f,    0.57f,0.86f,
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.57f,0.86f,
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.51f,0.56f,
		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.59f,0.38f,
		
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,1.0f,	0.22f,0.38f,		//inferior (2)		
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.332f,0.47f,
		0.5f,  -0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.302f,0.82f,
		0.5f,  -0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.302f,0.82f,
		-0.5f,  -0.5f, 0.5f,	1.0f, 1.0f,1.0f,    0.2f,0.72f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,1.0f,    0.22f,0.38f,
		
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f,1.0f,	0.83f,0.45f,				
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.92f,0.33f,
		0.5f,  0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.96f,0.66f,
		0.5f,  0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.96f,0.66f,
		-0.5f,  0.5f, 0.5f,		1.0f, 1.0f,1.0f,    0.87f,0.77f,
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f,1.0f,    0.83f,0.45f,
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Load textures
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D,texture1);
	int textureWidth, textureHeight,nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *image;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map
	image = stbi_load("images/wood_dice.jpg", &textureWidth, &textureHeight, &nrChannels,0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lampShader.Use();
		//// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 model(1);
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lampShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lampShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// Al presionar ESC, liberamos el mouse y dejamos de mover la cámara
		mouseCaptured = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		// Al presionar M, capturamos el mouse para mover la cámara
		mouseCaptured = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		firstMouse = true; // Reiniciamos para evitar saltos bruscos al activar
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) keys[key] = true;
		else if (action == GLFW_RELEASE) keys[key] = false;
	}
}
//void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
//{
//	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//		{
//			keys[key] = true;
//		}
//		else if (action == GLFW_RELEASE)
//		{
//			keys[key] = false;
//		}
//	}
//}
void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (!mouseCaptured) return;

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}
//void MouseCallback(GLFWwindow *window, double xPos, double yPos)
//{
//	if (firstMouse)
//	{
//		lastX = xPos;
//		lastY = yPos;
//		firstMouse = false;
//	}
//
//	GLfloat xOffset = xPos - lastX;
//	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
//
//	lastX = xPos;
//	lastY = yPos;
//
//	camera.ProcessMouseMovement(xOffset, yOffset);
//}