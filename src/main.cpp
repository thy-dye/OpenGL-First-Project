#include "window.hpp"
#include "renderloop/rendercontext.hpp"

//vertex and fragment shader 
const char *vertexShaderSource = "#version 400 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"    
    "out vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   ourColor = vec4(aColor, 1.0);\n"
    "}\0";
    
    const char *fragmentShaderSource = "#version 400 core\n"
    "out vec4 FragColor;\n"
    "in vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\0";
    

int main()
{
    Window w{WIDTH, HEIGHT, MAJOR, MINOR};
    RenderContext RomanCancel{w};
    RomanCancel.renderLoop();
}