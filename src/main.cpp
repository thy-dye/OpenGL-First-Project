#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define MAJOR 4
#define MINOR 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//vertex and fragment shader 
const char *vertexShaderSource = "#version 400 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 400 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.2f, 1.0f, 1.0f);\n"
    "}\0";
    

    int main()
{
    if (!glfwInit()) {
        std::cerr << "Unable to Initialize GLFW" << std::endl;
        return 1;
    }
    
    //hints to help glfw figure out opengl ver. + window dimensions
    constexpr int width = 800, height = 600;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); <-- GETS RID OF THE DEPRECATED FUNCTIONS
    
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    
    //load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }   
    
    //tell opengl how to size its viewport
    glViewport(0, 0, width, height);
    //tell glfw that when we resize the window to call this specific function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    int success;
    char infoLog[512];
        
    //compiling the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }    
    
    //compiling the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);   
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    
    //linking both shader objects
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); //pointer to program object
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);        
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //delete shader objects after we linked because they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //holds data of our vertices
    float vertices[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);                                                          //buffer id

    //create vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); 

    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                             //bind buffer to a type  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);      //use specified type to write our vertices to
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);   //tell opengl how to interpret the data
    glEnableVertexAttribArray(0);                                                   //enable the vertex attribute with the location as its argumetn
    
    //unbind it which we can do safely since glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    //glBindVertexArray(0); //we can also unbind the VAO but traditionally this is not done

    
    
    //render loop
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //todo fill with rendering functions at a later date
        //actually use our shader program
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); //normally there would be more than one VAO so you would bind as needed i think
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
    
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
}
