#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "../all.hpp"
#include "../window/window.hpp"
#include "../geometry/object.hpp"
#include "../camera/camera.hpp"

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
    
private:
    void render();
    Window *window;
    std::vector<Object*> objects;
    Camera camera;
    double lastFrameTime = 0, 
           delta_t = 0;
};