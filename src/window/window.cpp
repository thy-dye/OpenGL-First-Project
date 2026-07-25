#include "window.hpp"

// defining the static variables
int Window::inputModifiersEvent = 0;
Mouse Window::mouse{};
std::unordered_map<GLFWinput, int> Window::inputMap;

/****************************************************************************
Constructors and Destructor
*****************************************************************************/
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
    
    //framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    // glfw input callbacks
    glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetKeyCallback(window, processKeys);
    // glfw mouse callbacks
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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
*****************************************************************************/

// add and remove to the input map
int Window::addInput(const std::vector<GLFWinput>& input) 
{
    for (int i = 0; i < static_cast<int>(input.size()); ++i) 
    {
        inputMap[input[i]] = 0;
    }
    return 0;
}
int Window::removeInput(const std::vector<GLFWinput>& input) 
{
    for (int i = 0; i < static_cast<int>(input.size()); ++i) 
    {
        inputMap.erase(input[i]);
    }
    return 0;
}
void Window::clearInputs() 
{
    for (auto iter = inputMap.begin(); iter != inputMap.end(); ++iter)
    {
        iter->second = false;
    }
}

void Window::processMouse() 
{
    // err::log(INFO, std::to_string(glfwGetWindowAttrib(window, GLFW_HOVERED)) + " Window is Hovered");
    // err::log(INFO, std::to_string(glfwGetWindowAttrib(window, GLFW_FOCUSED)) + " Window is Focused");
    // err::log(INFO, std::to_string(isFocus) + " Window is focused custom logic");
    if ((glfwGetWindowAttrib(window, GLFW_HOVERED) &&  mouse.leftMouseButton == GLFW_PRESS) || isFocus) {
        if (mouse.wasOutside) { // mouse first time inside window
            glfwGetCursorPos(window, &mouse.xpos, &mouse.ypos);
            mouse.xoffset = mouse.yoffset = 0;
            mouse.wasOutside = false;
        }
        else { // mouse is still inside window
            double xpos=mouse.xpos, ypos=mouse.ypos;
            glfwGetCursorPos(window, &mouse.xpos, &mouse.ypos);
            mouse.xoffset = mouse.xpos - xpos; // new - old 
            mouse.yoffset = ypos - mouse.ypos; // y pos grows as we move down thats why its backwards
        }

        if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
            isFocus = true;
        }
        else { isFocus = false; }
    }
    else {
        mouse.wasOutside = true;
        isFocus = false;
    }
}

/****************************************************************************
Callbacks for GLFW
*****************************************************************************/

// called when the window changes size
void Window::framebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// called when any button is pressed or released
void Window::processModifiers([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int key, [[maybe_unused]] int scancode, int action, int mods)
{
    if (mods > 0 && action == GLFW_PRESS) { Window::inputModifiersEvent |= mods; }
    else                                  { Window::inputModifiersEvent = 0; }
}
void Window::processKeys([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
    err::log(INFO, std::to_string(inputMap[key]));
    err::log(INFO, std::to_string(key));
    if (inputMap.contains(key)) { inputMap[key] = action; }
}

// called when mouse buttons are clicked or released
void Window::mouseButtonCallback([[maybe_unused]] GLFWwindow* window, int button, int action, [[maybe_unused]]  int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)  { mouse.rightMouseButton  = action; }
    if (button == GLFW_MOUSE_BUTTON_LEFT)   { mouse.leftMouseButton   = action; }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) { mouse.middleMouseButton = action; }
}

// called when scrolled on mouse
void Window::mouseScrollCallback([[maybe_unused]] GLFWwindow* window,[[maybe_unused]] double xoffset,[[maybe_unused]] double yoffset)
{
    mouse.yscrolloffset = yoffset;
}