#include "window/window.hpp"
#include "shaders/shader.hpp"
#include "renderloop/rendercontext.hpp"
#include <string>
#include "geometry/object.hpp"
#include "error.hpp"
#include "geometry/halfedge.hpp"
#include "shaders/material.hpp"
#include <glm/gtc/type_ptr.hpp>
#define SHADER_PATH "C:/Users/Ty/Downloads/GitHub/OpenGL-First-Project/src/shaders/"

int main()
{
    Window w{WIDTH, HEIGHT, MAJOR, MINOR};

    std::string Path{SHADER_PATH};
    //this will eventually be the mesh class and an object class 
float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f
};   
    [[maybe_unused]]
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  
    
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO); 
    glGenBuffers(1, &EBO); 
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    std::string vert{Path + "main.vert"};
    std::string frag{Path + "main.frag"};
    Shader s(vert.c_str(), frag.c_str());
    Camera c{glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)};
    RenderContext RomanCancel{w, c};
    
    Object o;
    Mesh m;
    m.VAO = VAO;
    m.VBO = VBO;
    m.EBO = 0;
    o.shape = &m;
    Material l;
    l.s = &s;
    o.look = &l;

    RomanCancel.addObject(o);
    RomanCancel.renderLoop();
}