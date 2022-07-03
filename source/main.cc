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

// Declaring functions
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void errorCallback(int error, const char* description);
void keyProcessFunc(GLFWwindow *window);


// Global Variables
GLFWwindow* window;
double globalTime = glfwGetTime();
int GLFW_MAJOR, GLFW_MINOR, GLFW_REVISION;
int vertexAttribsMax;
float viewPos = -3.0f;
float viewSides = 0.0f;
double lastTime = glfwGetTime();
int nbFrames = 0;

int main ( void ) {
    // ---------------------------------------------------------------------------------------------------------------------------
    glfwInit();

    std::cout << "START: Initializing program\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(system_os == "Apple"){
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    if(!glfwInit()) { std::cout << "ERROR: Failed to start GLFW\n"; return -1;  } 
    
    std::cout << "INFO: Compiled with GLFW: " << GLFW_VERSION_MAJOR << GLFW_VERSION_MINOR << GLFW_VERSION_REVISION << "\n";
    glfwGetVersion(&GLFW_MAJOR, &GLFW_MINOR, &GLFW_REVISION);
    std::cout << "INFO: Running with GLFW: " << GLFW_MAJOR << GLFW_MINOR << GLFW_REVISION << "\n";

    window = glfwCreateWindow(800,800,"Minecraft", NULL, NULL);
    if(!window) { std::cout << "ERROR: Failed to create GLFW window\n"; glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "ERROR: Failed to initialized GLAD\n";
        glfwTerminate();
        return -1;
    }
    // ------------------------------------------------------------------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);
    Shader shader("./shaders/vertex.vertexshader", "./shaders/fragment.fragmentshader");

    //OpenGL Part

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Texture texture("../source/textures/metal.png");

    // WideMode, just drawing lines
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &vertexAttribsMax);
    std::cout << "INFO: Maximun of vertex attributes supported: " << vertexAttribsMax << "\n";

    /* 
    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    GL_STATIC_DRAW: the data is set only once and used many times.
    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */ 

    shader.use();

    do {
        //input 

        keyProcessFunc(window);
        glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, textureID);

        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0){
            std::cout << 1000.0/double(nbFrames) << " FPS\n";
            nbFrames = 0;
            lastTime += 1.0;
        }



        shader.use();

        
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(viewSides, 0.0f, viewPos));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);
        unsigned int modelLoc = glGetUniformLocation(shader.shaderProgramID, "model");
        unsigned int viewLoc = glGetUniformLocation(shader.shaderProgramID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        shader.setMat4("projection", projection);

        
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // swap and call events
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    } while (!glfwWindowShouldClose(window));
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    //glDeleteBuffers(1, &EBO);

    glfwTerminate();
    
    std::cout << "ENDLINE: Shutting down now\n";

    return 0;
}

// Callback function for errors
void errorCallback(int error, const char* description) {
    fprintf(stderr, "ERROR: %s\n", description);
}

// Callback function for resizing window
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Checking if esc key was pressed for closing window
void keyProcessFunc(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) viewPos += 0.3f;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) viewPos -= 0.3f;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) viewSides += 0.3f;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) viewSides -= 0.3f;
}
