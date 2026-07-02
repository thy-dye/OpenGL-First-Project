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
#include "all.hpp"

using GLFWinput = int;

/*Window Class
Member Objects:
map - Map for desired inputs to check
*/
class Window {
public:
    // Initialization function    
    Window(int width, int height, int Major, int minor);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete; 
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete; 

    // return a const reference to the current input map
    const std::unordered_map<GLFWinput, bool>& getInputMap() { return inputEvent; }
    
    // member functions
    GLFWwindow* getWindowContext() { return window; }
    void swapBuffer() { glfwSwapBuffers(window); }
    bool shouldClose() { return glfwWindowShouldClose(window); }
    void setClose() { glfwSetWindowShouldClose(window, GLFW_TRUE); }
    int addInput(std::vector<GLFWinput> input);
    int removeInput(std::vector<GLFWinput> input);
    void processInputs();
    void processMouse();
    void clearInputs();

private:
    // better for larger datasets so we will leave as is for now but has worse cache locality
    std::unordered_map<GLFWinput, bool> inputEvent;
    GLFWwindow *window;
};


//call backs for glfw defined in window.cpp
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
//glfwSetWindowCloseCallback() //may be needed in the future
