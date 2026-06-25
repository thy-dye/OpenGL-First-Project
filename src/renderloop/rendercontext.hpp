#pragma RENDERCONTEXT_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "all.hpp"
#include "window.hpp"


class RenderContext
{
    RenderContext();
    ~RenderContext();

    RenderContext(const RenderContext&) = delete;
    RenderContext& operator=(const RenderContext&) = delete; 
    RenderContext(RenderContext&&) = delete;
    RenderContext& operator=(RenderContext&&) = delete; 

    void renderLoop();

private:
    Window window;
    //todo these classes
    // std::vector<Shader> shader;
    // std::vector<Object> obj;
    // Camera camera
};