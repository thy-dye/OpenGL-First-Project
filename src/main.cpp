#include "window/window.hpp"
#include "shaders/shader.hpp"
#include "renderloop/rendercontext.hpp"
#include <string>
#include "geometry/object.hpp"
#include "error.hpp"
#include "geometry/halfedge.hpp"
#include "shaders/material.hpp"
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/string_cast.hpp>
#define SHADER_PATH "C:/Users/Ty/Downloads/GitHub/OpenGL-First-Project/src/shaders/"

int main()
{
    Window w{WIDTH, HEIGHT, MAJOR, MINOR};

    std::string Path{SHADER_PATH};
    //this will eventually be the mesh class and an object class 
    float vertices[] = {
        // positions         // colors
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f,
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
    RenderContext RomanCancel{w};
    
    Object o;
    Mesh m;
    m.VAO = VAO;
    m.VBO = VBO;
    m.EBO = 0;
    o.shape = &m;
    Material l;
    l.s = &s;
    o.look = &l;

    s.use();
    //model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //view matrix
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // projections
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    //send it to the shader but should be implemented in the render loop eventually 
    int modelLoc = glGetUniformLocation(s.getID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    modelLoc = glGetUniformLocation(s.getID(), "view");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(view));
    modelLoc = glGetUniformLocation(s.getID(), "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(projection));

    std::cout << glm::to_string(model) << std::endl;
    std::cout << glm::to_string(view) << std::endl;
    std::cout << glm::to_string(projection) << std::endl;

    RomanCancel.addObject(o);
    RomanCancel.renderLoop();
}