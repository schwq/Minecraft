#include "include.h"
#include "shaderCompiler.h"
#include "textureCompiler.h"

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

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void errorCallback(int error, const char* description);
void keyProcessFunc(GLFWwindow *window);

GLFWwindow* window;
double globalTime = glfwGetTime();
int GLFW_MAJOR, GLFW_MINOR, GLFW_REVISION;
int vertexAttribsMax;
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
    glfwSetErrorCallback(errorCallback);
    // Window resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

     // checking is GLAD initialized
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD"); 
        glfwTerminate();
        return -1;
    }

    //OpenGL Part

    float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader shader("./shaders/vertex.vertexshader", "./shaders/fragment.fragmentshader");
    
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Texture texture("../source/textures/obama.jpg");

    // WideMode, just drawing lines
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &vertexAttribsMax);
    printf("Maximun of Vertex Attributes supported: %i\n", vertexAttribsMax);

    /* 
    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    GL_STATIC_DRAW: the data is set only once and used many times.
    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */ 

    do {
        //input 

        keyProcessFunc(window);
        glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glm::mat4 transformation = glm::mat4(1.0f);
        transformation = glm::translate(transformation, glm::vec3(0.5f, -0.5f, 0.0f));
        transformation = glm::rotate(transformation, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));


        shader.use();
        unsigned int transformationLoc = glGetUniformLocation(shader.shaderProgramID, "transform");
        glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, glm::value_ptr(transformation));
        
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // swap and call events
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    } while (!glfwWindowShouldClose(window));
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

// Callback function for errors
void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

// Callback function for resizing window
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Checking if esc key was pressed for closing window
void keyProcessFunc(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
