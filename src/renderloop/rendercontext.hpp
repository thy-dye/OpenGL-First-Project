#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <glm/glm.hpp>
#include "../all.hpp"
#include "../window/window.hpp"
#include "../geometry/object.hpp"
#include "../camera/camera.hpp"

enum RenderContextState { WORLDSPACE, OBJECTSPACE };
typedef int ContextState;

class RenderContext
{
public:
    RenderContext(Window& window);
    ~RenderContext();

    RenderContext(RenderContext&) = delete;
    RenderContext& operator=(const RenderContext&) = delete; 
    RenderContext(RenderContext&&) = delete;
    RenderContext& operator=(RenderContext&&) = delete; 

    //may need to add objects in such a way to utilize unique_ptr
    void addObject(Object& o);
    void renderLoop();

//getter functions if i have more internal variables
    double deltaTime() { return delta_t; };

private:
    void render();
    Window *window;
    std::vector<Object*> objects;
    Camera camera;
    double lastFrameTime = 0, 
           delta_t = 0;
    ContextState state = WORLDSPACE;

};