#include "window.hpp"

Window::Window(int major=4, int minor=0, int width, int height) 
{
    //initialize glfw
    if (!glfwInit()) {
        std::cerr << "Unable to Initialize GLFW" << std::endl;
        // return 1 figure out error handling
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "BENDECIDO", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // return 1 again here
    }
    glfwMakeContextCurrent(window);

    //load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // return 1 again here
    }   

    //tell opengl how to size its viewport
    glViewport(0, 0, width, height);
    //tell glfw that when we resize the window to call this specific function
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // setup function for callbacks
}

Window::~Window() 
{

}