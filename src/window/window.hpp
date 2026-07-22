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
    float xpos, ypos, xoffset, yoffset;
    float yscrolloffset;
    bool rightMouseButton, leftMouseButton;
    
};

/*Window Class
Member Objects:
map - Map for desired inputs to check
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

    //add a function to remove all inputs
    void processInputs();
    void processMouse();
    void clearInputs();
    
    // return a const reference to the current input map
    const std::unordered_map<GLFWinput, bool>& getInputMap() { return inputEvent; }
    int getModifiers() { return Window::inputModifiersEvent; }
    const Mouse& getMouse() { return mouse; }
private:
    //static functions for callbacks
    //input callbacks
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void processModifiers(GLFWwindow* window, int key, int scancode, int action, int mods);
    //mouse callbacks
    static void cursorPosCallBack(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    
    // better for larger datasets so we will leave as is for now but has worse cache locality
    static int inputModifiersEvent;
    std::unordered_map<GLFWinput, bool> inputEvent;
    GLFWwindow *window;
    static Mouse mouse;
};

//implement these as static methods for the callback
//call backs for glfw defined in window.cpp
//glfwSetWindowCloseCallback() //may be needed in the future
