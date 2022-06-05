#include "include.h"
#include "shaderCompiler.h"

// Detected operating system
constexpr const char system_os[] =
#if defined(_WIN32) || defined(__CYGWIN__)
"Windows";
#elif defined( __APPLE__)
"Apple";
#elif defined(__linux__)
"Linux";
#else
 #error
#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void error_callback(int error, const char* description);
void escape_pressed(GLFWwindow *window);

GLFWwindow* window;
double global_time = glfwGetTime();
int GLFW_MAJOR, GLFW_MINOR, GLFW_REVISION;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main ( void ) {

    glfwInit();

    // OpenGL minimum version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(system_os == "Apple"){
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

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

    // Make context 
    glfwMakeContextCurrent(window);
    // GLFW error handing callback
    glfwSetErrorCallback(error_callback);
    // Window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

     // checking is GLAD initialized
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD"); 
        glfwTerminate();
        return -1;
    }

    //OpenGL Part

    float vertices_coordinates[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f  
    };

    // Vertex Buffer Object
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_coordinates), vertices_coordinates, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint ProgramID = shaderCompiler("./shaders/vertex.vertexshader", "./shaders/fragment.fragmentshader");
    

    /* 
    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    GL_STATIC_DRAW: the data is set only once and used many times.
    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */ 


    do {
        //input 
        escape_pressed(window);

        glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(ProgramID);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap and call events
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    } while (!glfwWindowShouldClose(window));
    
    glfwTerminate();
    return 0;
}

// Callback function for errors
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

// Callback function for resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Checking if esc key was pressed for closing window
void escape_pressed(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}