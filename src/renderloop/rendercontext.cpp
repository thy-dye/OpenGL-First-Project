#include "rendercontext.hpp"

RenderContext::RenderContext(Window& w) 
{
    window = &w;
}

//todo as we continually update this class
RenderContext::~RenderContext()
{

}

//main render loop
void RenderContext::renderLoop()
{
    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //todo fill with rendering functions at a later date
        //actually use our shader program
        // float timeValue = glfwGetTime();
        // float blueValue = (std::sin(timeValue) / 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        // glUniform4f(vertexColorLocation, 0.0f, 0.0f, blueValue, 1.0f);
        glBindVertexArray(VAO); //normally there would be more than one VAO so you would bind as needed i think
        // glDrawArrays(GL_TRIANGLES, 0, 3); //renderes using array of verts (VBO)
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //renders using indices of the EBO into the VBO
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        //render ImGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}