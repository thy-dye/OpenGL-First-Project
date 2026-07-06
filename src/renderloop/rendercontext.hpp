#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "../all.hpp"
#include "../window/window.hpp"
#include "../geometry/object.hpp"

class RenderContext
{
public:
    RenderContext(Window& window);
    ~RenderContext();

    RenderContext(RenderContext&) = delete;
    RenderContext& operator=(const RenderContext&) = delete; 
    RenderContext(RenderContext&&) = delete;
    RenderContext& operator=(RenderContext&&) = delete; 

    void addObject(Object& o);
    void renderLoop();
    void render();

private:
    Window *window;
    std::vector<Object*> objects;
    //todo these classes
    // std::vector<Object> obj;
    // Camera camera
};