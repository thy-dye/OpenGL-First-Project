#pragma WINDOW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
private:    
    Window(int Major=4, int minor=0, int width, int height);
    ~Window();
    Window(const Window& window) = delete;
    Window& operator=(const Window& window) = delete; 
    Window(Window&& window) = delete;
    Window& operator=(Window&& window) = delete; 

public:
    GLFWwindow* window;
    
};