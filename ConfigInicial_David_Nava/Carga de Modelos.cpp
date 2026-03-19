//Practica 6                  Nava Benítez David Emilio
// 20 de marzo de 2026      320291599
// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
bool mouseCaptured = false;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Carga de modelos y camara sintetica - Practica6_David_Nava", nullptr, nullptr );
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent( window );
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Load models
    Model dog((char*)"Models/RedDog.obj");
    Model corgi((char*)"Models/Corgi.obj");
    Model office((char*)"Models/Practica6/Entorno/InteriorHouse.obj");
    Model table((char*)"Models/Practica6/Mesa/Table.obj");
    Model paper((char*)"Models/Practica6/Papeleria/Holder_and_shelf.obj");
    Model chair((char*)"Models/Practica6/Silla/office chair.obj");
    Model bookcase((char*)"Models/Practica6/Librero/bookcase.obj");
    Model books((char*)"Models/Practica6/Books/bookpack_001_obj.obj");
    Model dogbed((char*)"Models/Practica6/DogBed/pet_bed.obj");
    Model sofa((char*)"Models/Practica6/Sillon/armchair.obj");
    Model clock((char*)"Models/Practica6/Reloj/Clock.obj");
    Model anotherTable((char*)"Models/Practica6/Table/ASSET.obj");
    Model cuadro((char*)"Models/Practica6/Cuadro/SM_Frame_Ornate_01.obj");
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Check and call events
        glfwPollEvents();
        DoMovement();
        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));


        //Modelo de oficina
        glm::mat4 model(1);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        office.Draw(shader);
        //Modelo de mesa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.45f, 0.01f, 0.8f));
        model = glm::rotate(model, 3.1415f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        table.Draw(shader);
        //Modelo papeleria
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.37f, 0.3f, 0.84f));
        model = glm::rotate(model, 3.1415f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        paper.Draw(shader);
        //Modelo Silla
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.75f, -0.085f, 0.5f));
        model = glm::rotate(model, 0.78f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        chair.Draw(shader);
        //Modelo libreros
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.05f, 0.0f, 1.5f));
        model = glm::rotate(model, 3.1415f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bookcase.Draw(shader);
        
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.05f, 0.0f, 2.0f));
        model = glm::rotate(model, 3.1415f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bookcase.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.05f, 0.0f, 2.5f));
        model = glm::rotate(model, 3.1415f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bookcase.Draw(shader);
        //Modelo libros
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.05f, 0.67f, 1.63f));
        model = glm::rotate(model, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.0005f, 0.0005f, 0.0005f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        books.Draw(shader);
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.05f, 0.67f, 1.55f));
        model = glm::rotate(model, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.0005f, 0.0005f, 0.0005f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        books.Draw(shader);
        //Cama perrito
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.4f, 0.0f, 0.2f));
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dogbed.Draw(shader);
        //Perrito Original
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.4f, 0.19f, 0.2f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);
        //Corgi
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.52f, 0.24f, 0.53f));
        model = glm::scale(model, glm::vec3(0.0015f, 0.0015f, 0.0015f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        corgi.Draw(shader);
        //Sofa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.0f, -0.015f, 1.55f));
        model = glm::rotate(model, -0.78f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sofa.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.0f, -0.015f, 2.19f));
        model = glm::rotate(model, -2.356f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sofa.Draw(shader);
        //Reloj
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.61f, 0.75f, 2.8f));
        model = glm::rotate(model, 3.1415f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.095f, 0.095f, 0.095f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        clock.Draw(shader);
        //Mesita
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.15f, 0.0f, 1.87f));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        anotherTable.Draw(shader);
        //Cuadro
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.5f, 0.75f, 2.8f));
        model = glm::rotate(model, 3.1415f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuadro.Draw(shader);

       

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
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
//void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
//{
//    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
//    {
//        glfwSetWindowShouldClose(window, GL_TRUE);
//    }
//    
//    if ( key >= 0 && key < 1024 )
//    {
//        if ( action == GLFW_PRESS )
//        {
//            keys[key] = true;
//        }
//        else if ( action == GLFW_RELEASE )
//        {
//            keys[key] = false;
//        }
//    }
//
// 
//
// 
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
//void MouseCallback( GLFWwindow *window, double xPos, double yPos )
//{
//    if ( firstMouse )
//    {
//        lastX = xPos;
//        lastY = yPos;
//        firstMouse = false;
//    }
//    
//    GLfloat xOffset = xPos - lastX;
//    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
//    
//    lastX = xPos;
//    lastY = yPos;
//    
//    camera.ProcessMouseMovement( xOffset, yOffset );
//}
//
