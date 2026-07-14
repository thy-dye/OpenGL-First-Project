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
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

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
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    window->swapBuffer();
}

void RenderContext::addObject(Object& o)
{
    objects.push_back(&o);
}