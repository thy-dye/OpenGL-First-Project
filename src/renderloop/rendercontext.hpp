#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "../all.hpp"
#include "../window/window.hpp"


class RenderContext
{
public:
    RenderContext(Window& window);
    ~RenderContext();

    RenderContext(RenderContext&) = delete;
    RenderContext& operator=(const RenderContext&) = delete; 
    RenderContext(RenderContext&&) = delete;
    RenderContext& operator=(RenderContext&&) = delete; 

    void renderLoop();
    void render();

private:
    Window *window;
    //todo these classes
    // std::vector<Shader> shader;
    // std::vector<Object> obj;
    // Camera camera
};