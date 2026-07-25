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
    bool getCameraMode()             { return cameraMode; }

private:
    // private member functions
    void render();
    void rotateCamera(bool cm);
    void processInputs();

    Window *window;
    //eventually change from a ptr to a unique ptr im not sure why as well can look into that
    std::vector<Object*> objects; 
    float lastFrameTime = 0, 
    dt = 0;
    int frameLimit;
    RenderContextState contextState = WORLDSPACE;

    // data for the camera usage
    // many functions rely on cameraMode so if the type changes to support more modes change those as well
    bool cameraMode = FLYMODE;
    Camera camera;
    PerspectiveMode perspectiveMode = PERSPECTIVE;
    glm::vec3 dir;
    float yaw=-90.0f, pitch=0;

};
//todo add a sleep functionality and a framerate cap