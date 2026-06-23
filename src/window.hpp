#pragma WINDOW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


#define MAJOR 4
#define MINOR 0

class Window {
private:    
    Window(int Major=MAJOR, int minor=MINOR, int width, int height);
    ~Window();
    Window(const Window& window) = delete;
    Window& operator=(const Window& window) = delete; 
    Window(Window&& window) = delete;
    Window& operator=(Window&& window) = delete; 

public:
    GLFWwindow* window;
    
};