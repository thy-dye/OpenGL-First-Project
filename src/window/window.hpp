#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
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
    int rightMouseButton, leftMouseButton, middleMouseButton;
    bool wasOutside=true;
};

/*
Window Class
Inputs are either Pressed=1, repeated=2, or released=0
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
    
        // input map
    int addInput(const std::vector<GLFWinput>& input);
    int removeInput(const std::vector<GLFWinput>& input);
    void clearInputs();
    static void clearMouseButtons();
    static void clearMouseScroll() { mouse.yscrolloffset = 0; }

        // cursor options
    void setDisabledCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
    void setNormalCursor()   { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

    // process functions
    void processMouse();
    
    // getter functions
    GLFWinput getKeyState(GLFWinput i) { return glfwGetKey(window, i); } //used for continuous pressing
    const std::unordered_map<GLFWinput, int>& getInputMap() { return inputMap; } //used for singular press
    int getModifiers() { return Window::inputModifiersEvent; } 
    const Mouse& getMouse() { return mouse; }
    bool isFocused() { return isFocus; }
    
private:
    //static functions for callbacks
    // window size callback
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    //keyboard callbacks
    static void processModifiers(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void processKeys(GLFWwindow* window, int key, int scancode, int action, int mods);

    //mouse callbacks
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    
    bool isFocus = false;
    static int inputModifiersEvent;
    // better for larger datasets but worse cache locality
    static std::unordered_map<GLFWinput, int> inputMap;
    GLFWwindow *window;
    static Mouse mouse;
};
