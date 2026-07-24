#include "rendercontext.hpp"

/****************************************************************************
Constructor and Destructor
*****************************************************************************/

RenderContext::RenderContext(Window& window, Camera& camera, int frameLimit) : frameLimit{frameLimit} , camera{camera}
{
    this->window = &window;
    std::vector v = {GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_TAB};
    window.addInput(v);
}

//todo as we continually update this class
RenderContext::~RenderContext()
{

}

/****************************************************************************
Member Functions
*****************************************************************************/

void RenderContext::addObject(Object& o)
{
    objects.push_back(&o);
}

/***************** MAIN LOOP *****************/
void RenderContext::renderLoop()
{
    while(!window->shouldClose()) 
    {
        // get time frame
        dt = glfwGetTime() - lastFrameTime;
        lastFrameTime = glfwGetTime();
    
        if (!ImGui::GetIO().WantCaptureKeyboard) { 
            window->processInputs();
        }

        if (!ImGui::GetIO().WantCaptureMouse) { 
            window->processMouse();
            if (window->isFocused()) { //check if window is focused
                rotateCamera(cameraMode);
            }
        }

        auto map = window->getInputMap();
        if (map[GLFW_KEY_ESCAPE]) { 
            window->setClose(); 
        }
        if (map[GLFW_KEY_W]) { camera.pos += camera.cameraSpeed * camera.getForward() * dt; } 
        if (map[GLFW_KEY_S]) { camera.pos += camera.cameraSpeed * -camera.getForward() * dt; }
        if (map[GLFW_KEY_D]) { camera.pos += camera.cameraSpeed * camera.getRight() * dt; }
        if (map[GLFW_KEY_A]) { camera.pos += camera.cameraSpeed * -camera.getRight() * dt; }
        if (map[GLFW_KEY_TAB]) { cameraMode = !cameraMode; }

        [[maybe_unused]]int mods = window->getModifiers();
        glfwPollEvents();
        render();
    }
}

/****************************************************************************
Private functions
*****************************************************************************/

// actual fucntion to render
void RenderContext::render()
{
    //opengl rendering
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);  

    for (int i = 0; i < static_cast<int>(objects.size()); ++i)
    {
        objects[i]->look->s->use();
        //i can do this only cus its the only object rn
        //model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        //view matrix
        glm::mat4 view = camera.lookAt();

        // projections
        glm::mat4 projection = camera.perspectiveProjection();

        objects[i]->look->s->setMat4("model", model);
        objects[i]->look->s->setMat4("view", view);
        objects[i]->look->s->setMat4("projection", projection);    
        
        glBindVertexArray(objects[i]->shape->VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //renders using array of indices (EBO)
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    //imgui ui demo
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        // we HAVE to reset the glfw context idk why but we have to
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    window->swapBuffer();
}

void RenderContext::rotateCamera(bool cm) 
{
    if (cm == FLYMODE) {
        window->setDisabledCursor();
        yaw   += window->getMouse().xoffset * 0.1f;  ///error has something to do with the permanent offset or something like that
        pitch += window->getMouse().yoffset * 0.1f; 
        if(pitch > 89.0f)  { pitch =  89.0f; }
        if(pitch < -89.0f) { pitch = -89.0f; } 
        dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        dir.y = sin(glm::radians(pitch));
        dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        err::log(INFO, std::to_string(window->getMouse().xpos) + " Pos x");
        err::log(INFO, std::to_string(window->getMouse().ypos) + " Pos y");
        err::log(INFO, std::to_string(window->getMouse().xoffset) + " Offset x");
        err::log(INFO, std::to_string(window->getMouse().yoffset) + " Offset y");

        err::log(INFO, glm::to_string(dir));
        err::log(INFO, glm::to_string(camera.forward));
        camera.forward = glm::normalize(dir);
    }
    else {
        window->setNormalCursor();
        err::log(INFO, "not implemented yet");
    }
}