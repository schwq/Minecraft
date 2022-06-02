// Basic group
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <memory>
#include <algorithm>

// OPENGL group
#include <GL/gl.h>
#include <glm/glm.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//#include <GL/glew.h>
//#include <GL/glut.h>

GLFWwindow* window;
double global_time = glfwGetTime();
int GLFW_MAJOR, GLFW_MINOR, GLFW_REVISION;

// Error Function
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main ( void ) {

    glfwInit();

    // GLFW error handing callback
    glfwSetErrorCallback(error_callback);
    // OpenGL minimum version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Checking if glfw initialized
    if(!glfwInit()) { printf("Failed to Initialized GLFW"); return -1;  } 
    
    printf("Compiled with GLFW %i.%i.%i\n", 
        GLFW_VERSION_MAJOR, 
        GLFW_VERSION_MINOR, 
        GLFW_VERSION_REVISION);
    glfwGetVersion(&GLFW_MAJOR, &GLFW_MINOR, &GLFW_REVISION);
    printf("Running with GLFW %i.%i.%i\n", GLFW_MAJOR, GLFW_MINOR, GLFW_REVISION);

    // Create Window
    window = glfwCreateWindow(800,800,"Minecraft", NULL, NULL);
    if(!window) { printf("Failed to Initialized GLFW\n"); glfwTerminate(); return -1; }
    
    // Interval between swaping buffer (1sec), computers usually run on 60fps, so swaping with 0sec of interval consumes a lot of the cpu cycles.
    glfwSwapInterval(1);

    // Make context 
    glfwMakeContextCurrent(window);

    //OpenGL Part

    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    } while (!glfwWindowShouldClose(window));
    return 0;
}

