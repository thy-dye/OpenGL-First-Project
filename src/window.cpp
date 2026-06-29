#include "window.hpp"

//constructor
Window::Window(int width, int height, int major=4, int minor=0)
{
    // initialize glfw
    if (!glfwInit()) {
        err::log(LogLevel::CRIT, "Unable to initialize GLFW");
        throw std::runtime_error("");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "BENDECIDO", NULL, NULL);

    if (window == NULL) {
        err::log(LogLevel::CRIT, "Unable to create a GLFW window");
        glfwTerminate();
        throw std::runtime_error("");
    }
    glfwMakeContextCurrent(window);
    //load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        err::log(LogLevel::CRIT, "Failed to initialize Glad");   
        glfwTerminate(); 
        throw std::runtime_error("");
    }   
    
    //tell opengl how to size its viewport
    glViewport(0, 0, width, height);
    //tell glfw that when we resize the window to call this specific function
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

    //initialize dear imgui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    //todo enable more flags ifykyk
    int flags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= flags;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

// destructor
Window::~Window() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

// member functions

//for the add and remove unsure if they would crash would need to look more into
//that and figure out how to prevent it from crashing
int Window::addInput(std::vector<GLFWinput> input) 
{
    for (int i = 0; i < static_cast<int>(input.size()); ++i) 
    {
        inputEvent[input[i]] = false;
    }
    return 0;
}

int Window::removeInput(std::vector<GLFWinput> input) 
{
    for (int i = 0; i < static_cast<int>(input.size()); ++i) 
    {
        inputEvent.erase(input[i]);
    }
    return 0;
}

//read into glfw mods
void Window::processInputs() 
{
    for (auto iter = inputEvent.begin(); iter != inputEvent.end(); ++iter)
    {
        if (glfwGetKey(window, iter->first) == GLFW_PRESS) { iter->second = true; }
        else { iter->second = false; }
    }
}
//todo
void Window::processMouse() 
{
    err::log(LogLevel::INFO, "method not created yet");
}

void Window::clearInputs() 
{
    for (auto iter = inputEvent.begin(); iter != inputEvent.end(); ++iter)
    {
        iter->second = false;
    }
}


/* CALLBACK SECTION FOR GLFW */


void framebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//todo the scroll callback should be for the camera focal length
void scrollCallback([[maybe_unused]] GLFWwindow* window,[[maybe_unused]] double xoffset,[[maybe_unused]] double yoffset)
{
    err::log(LogLevel::INFO, "method not created yet");
}