#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../all.hpp"

using GLFWinput = int;

// assumes a normal mouse with two buttons and one scroll wheel direction
// when implementing graph edits will need to utilize glfwsetinputmode GLFW_CURSOR_HIDDEN for functionality 
struct Mouse {
    double xpos, ypos, xoffset=0, yoffset=0;
    double yscrolloffset;
    bool rightMouseButton, leftMouseButton, middleMouseButton,
        wasOutside=true;
    
};

/*Window Class
*/
class Window {
public:
    // Constructor   
    Window(int width, int height, int Major=MAJOR, int minor=MINOR);
    // Destructor
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete; 
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete; 

    
    // member functions
    GLFWwindow* getWindowContext() { return window; }
    void swapBuffer() { glfwSwapBuffers(window); }
    bool shouldClose() { return glfwWindowShouldClose(window); }
    void setClose() { glfwSetWindowShouldClose(window, GLFW_TRUE); }
    int addInput(std::vector<GLFWinput> input);
    int removeInput(std::vector<GLFWinput> input);
    void setDisabledCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
    void setNormalCursor()   { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

    // input functions
    void processInputs();
    void processMouse();
    void clearInputs();
    
    // getter functions
    const std::unordered_map<GLFWinput, bool>& getInputMap() { return inputEvent; }
    int getModifiers() { return Window::inputModifiersEvent; }
    const Mouse& getMouse() { return mouse; }
    bool isFocused() { return isFocus; }
    
private:
    //static functions for callbacks
    //keyboard callbacks
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void processModifiers(GLFWwindow* window, int key, int scancode, int action, int mods);
    //mouse callbacks
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    
    bool isFocus = false;
    static int inputModifiersEvent;
    // better for larger datasets so we will leave as is for now but has worse cache locality
    std::unordered_map<GLFWinput, bool> inputEvent;
    GLFWwindow *window;
    static Mouse mouse;
};
