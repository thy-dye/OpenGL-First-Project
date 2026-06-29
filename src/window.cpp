#include "window.hpp"

//constructor
Window::Window(int major=4, int minor=0, int width, int height) 
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // setup function for callbacks

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
int Window::addEvent(std::vector<GLFWinput> events) 
{
    for (int i = 0; i < events.size(); ++i) 
    {
        inputEvent[events[i]] = false;
    }
}

int Window::removeEvent(std::vector<GLFWinput> events) 
{
    for (int i = 0; i < events.size(); ++i) 
    {
        inputEvent.erase(events[i]);
    }
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

void Window::swapBuffer() { glfwSwapBuffers(window); }

bool Window::shouldClose() { return glfwWindowShouldClose(window); }

void Window::clearInputs() 
{
    for (auto iter = inputEvent.begin(); iter != inputEvent.end(); ++iter)
    {
        iter->second = false;
    }
}