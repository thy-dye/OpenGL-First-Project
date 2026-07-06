#include "window/window.hpp"
#include "shaders/shader.hpp"
#include "renderloop/rendercontext.hpp"
#include <string>
#include "geometry/object.hpp"

#define SHADER_PATH "C:/Users/Ty/Downloads/GitHub/OpenGL-First-Project/src/shaders/"

int main()
{
    std::string Path{SHADER_PATH};
    //this will eventually be the mesh class and an object class 
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    [[maybe_unused]]
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); 

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0); //unbind

    std::string vert{Path + "main.vert"};
    std::string frag{Path + "main.frag"};
    Shader s(vert.c_str(), frag.c_str());
    Window w{WIDTH, HEIGHT, MAJOR, MINOR};
    RenderContext RomanCancel{w};

    Object o;
    o.shape->VAO = VAO;
    o.shape->VBO = VBO;
    o.shape->EBO = 0;
    o.look->s = &s;
    RomanCancel.addObject(o);
    RomanCancel.renderLoop();
}