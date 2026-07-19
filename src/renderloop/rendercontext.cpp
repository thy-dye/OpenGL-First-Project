#include "rendercontext.hpp"

/****************************************************************************
Constructor and Destructor
*****************************************************************************
*/

RenderContext::RenderContext(Window& window, Camera& camera) : camera{camera} 
{
    this->window = &window;
    std::vector v = {GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D};
    window.addInput(v);
}

//todo as we continually update this class
RenderContext::~RenderContext()
{

}

/****************************************************************************
Member Functions
*****************************************************************************
*/

void RenderContext::addObject(Object& o)
{
    objects.push_back(&o);
}

/***************** MAIN LOOP *****************/
void RenderContext::renderLoop()
{
    delta_t = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();

    while(!window->shouldClose()) 
    {
        if (!ImGui::GetIO().WantCaptureKeyboard) { 
            window->processInputs();
        }

        if (!ImGui::GetIO().WantCaptureMouse) { 
            window->processMouse();
        }

        auto map = window->getInputMap();
        if (map[GLFW_KEY_ESCAPE]) { 
            window->setClose(); 
            err::log(LogLevel::INFO, "Esc is pressed");
        }

        int temp = window->getModifiers();
        if (temp & GLFW_MOD_SHIFT)   { err::log(LogLevel::INFO, "Shift is pressed");}
        if (temp & GLFW_MOD_CONTROL) { err::log(LogLevel::INFO, "ctrl is pressed");}
        glfwPollEvents();
        render();
    }
}

// rendering function
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
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

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