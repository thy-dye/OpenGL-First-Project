#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include "../error.hpp"

enum ShaderType
{
    VERTEX_SHADER,
    TESSELLATION_SHADER_1,
    TESSELLATION_SHADER_2,
    GEOMETRY_SHADER,
    FRAGMENT_SHADER
};

class Shader 
{
public:

//create a shader
Shader();
Shader(const char *vertexPath, const char *fragmentPath);
Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath);
~Shader();
// copy assignment
Shader(const Shader& s) = delete;
Shader operator=(const Shader& s) = delete;
//move assignment 
Shader(Shader&& s);
Shader& operator=(Shader&& s);

//activate shader
void use() { glUseProgram(ID); }
//reload the shader for quality of life
void reloadShader(const char *vertexPath=nullptr, const char *geometryPath=nullptr, const char *fragmentPath=nullptr);
//utility uniform functions
void setBool(const std::string &name, bool value) const;
void setInt(const std::string &name, int value) const;
void setFloat(const std::string &name, float value) const;
void setVec4(const std::string &name, float v1, float v2, float v3, float v4) const;
void setVec3(const std::string &name, float v1, float v2, float v3) const;
void setVec2(const std::string &name, float v1, float v2) const;
void setMat4(const std::string &name, const glm::mat4& M) const;
void setMat3(const std::string &name, const glm::mat3& M) const;
void setMat2(const std::string &name, const glm::mat2& M) const;

// std::ifstream tessFile; //here for future creep scope? THIS WILL BECOME AN ARRAY IN THE FUTURE BRUH
int success;

private:

void loadShader(const char* shader, int shadertype);
void createShader();

std::ifstream vertFile;
std::ifstream geoFile;
std::ifstream fragFile;

unsigned int ID;
const char *vPath = nullptr;
const char *gPath = nullptr;
const char *fPath = nullptr;
};

// for future maybe add opengl 4.3 to add compute shaders and textures support