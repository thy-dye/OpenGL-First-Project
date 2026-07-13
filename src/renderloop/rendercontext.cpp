#include "rendercontext.hpp"

RenderContext::RenderContext(Window& window) 
{
    this->window = &window;
    std::vector v = {GLFW_KEY_ESCAPE};
    window.addInput(v);
}

//todo as we continually update this class
RenderContext::~RenderContext()
{

}

//main render loop
void RenderContext::renderLoop()
{
    // helper variables for time
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
        if (map[GLFW_KEY_ESCAPE]) { window->setClose(); }
        glfwPollEvents();
        render();
    }
}

void RenderContext::render()
{
    //opengl rendering
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //todo fill with rendering functions at a later date using inputs, mesh, and a shader class

    for (int i = 0; i < static_cast<int>(objects.size()); ++i)
    {
        objects[i]->look->s->use();
        glBindVertexArray(objects[i]->shape->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //renderes using array of indices (EBO)
    }
    
    //imgui ui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    window->swapBuffer();
}

void RenderContext::addObject(Object& o)
{
    objects.push_back(&o);
}