#include "window/window.hpp"
#include "shaders/shader.hpp"
#include "renderloop/rendercontext.hpp"

#define VERTPATH
#define FRAGPATH

int main()
{
    Window w{WIDTH, HEIGHT, MAJOR, MINOR};
    RenderContext RomanCancel{w};
    RomanCancel.renderLoop();
}