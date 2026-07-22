#include "window.hpp"

// defining the static variable
int Window::inputModifiersEvent = 0;
Mouse Window::mouse{};

/****************************************************************************
Constructors and Destructor
*****************************************************************************
*/
Window::Window(int width, int height, int major, int minor) 
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
    // glfw input callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetKeyCallback(window, processModifiers);
    // pollable state of a key will remain GLFW_PRESS until the state of that key is polled with glfwGetKey
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE); // if you are going to use sticky keys might need to look into how to have a focused and unfocused window
    //TODO ADD SCROLL AND MOUSE

    // glfw mouse callbacks
    glfwSetCursorPosCallback(window, cursorPosCallBack);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
    //initialize dear imgui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    int flags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad | 
                ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= flags;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

Window::~Window() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

/****************************************************************************
Member Functions
*****************************************************************************
*/

// add and remove to the input map
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

// Process various inputs
void Window::processInputs() 
{
    for (auto iter = inputEvent.begin(); iter != inputEvent.end(); ++iter)
    {
        if (glfwGetKey(window, iter->first) == GLFW_PRESS) { iter->second = true; }
        else { iter->second = false; }
    }
}
void Window::clearInputs() 
{
    for (auto iter = inputEvent.begin(); iter != inputEvent.end(); ++iter)
    {
        iter->second = false;
    }
}

/* CALLBACK SECTION FOR GLFW */

// called when the window changes size
void Window::framebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//called when any button is pressed or released
void Window::processModifiers([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int key, [[maybe_unused]] int scancode, int action, int mods)
{
    if (mods > 0 && action == GLFW_PRESS) { Window::inputModifiersEvent |= mods; }
    else                                  { Window::inputModifiersEvent = 0; }
}

void Window::cursorPosCallBack([[maybe_unused]] GLFWwindow* window, double xpos, double ypos) 
{
    mouse.xoffset = static_cast<float>(xpos) - mouse.xpos;
    mouse.yoffset = static_cast<float>(ypos) - mouse.ypos; 
    mouse.xpos = static_cast<float>(xpos);
    mouse.ypos = static_cast<float>(ypos);
}

void Window::mouseButtonCallback([[maybe_unused]] GLFWwindow* window, int button, int action, [[maybe_unused]]  int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) { mouse.rightMouseButton = true; }
    else { mouse.rightMouseButton = false; }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) { mouse.leftMouseButton = true; }
    else { mouse.leftMouseButton = false; }
}

void Window::mouseScrollCallback([[maybe_unused]] GLFWwindow* window,[[maybe_unused]] double xoffset,[[maybe_unused]] double yoffset)
{
    mouse.yoffset = yoffset;
}