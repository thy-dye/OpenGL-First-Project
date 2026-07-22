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

class RenderContext
{
public:
    RenderContext(Window& window, Camera& camera, int frameLimit=180);
    ~RenderContext();

    RenderContext(RenderContext&) = delete;
    RenderContext& operator=(const RenderContext&) = delete; 
    RenderContext(RenderContext&&) = delete;
    RenderContext& operator=(RenderContext&&) = delete; 

    //may need to add objects in such a way to utilize unique_ptr
    void addObject(Object& o);
    void renderLoop();

//getter functions if i have more internal variables
    double deltaTime()               { return dt; };
    RenderContextState getState()    { return contextState; }
    CameraMode getCameraMode()       { return cameraMode; }

private:
    void render();
    Window *window;
    std::vector<Object*> objects; //eventually change from a ptr to a unique ptr im not sure why as well can look into that
    Camera camera;
    float lastFrameTime = 0, 
           dt = 0;
    int frameLimit;
    RenderContextState contextState = WORLDSPACE;
    CameraMode cameraMode = FLYMODE;

    //this is a temp space for these until i figure where to put them
    glm::vec3 dir;
    float yaw=-90.0f, pitch;

};
//todo add a sleep functionality and a framerate cap