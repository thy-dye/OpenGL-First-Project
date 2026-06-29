#pragma WINDOW_HPP
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

/*
*/
class Window {
public:
    // Initialization function    
    Window(int Major, int minor, int width, int height);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete; 
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete; 

    // return a const reference to the current input map
    const std::unordered_map<GLFWinput, bool>& getInputMap() { return inputEvent; }
    GLFWwindow* getWindowContext() { return window; }

    // member functions
    int addEvent(std::vector<GLFWinput> events);
    int removeEvent(std::vector<GLFWinput> events);
    void processInputs();
    void swapBuffer();
    bool shouldClose();
    void clearInputs();

private:
    // better for larger datasets so we will leave as is for now but has worse cache locality
    std::unordered_map<GLFWinput, bool> inputEvent;
    GLFWwindow *window;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}