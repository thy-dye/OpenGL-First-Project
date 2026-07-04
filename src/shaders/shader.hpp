#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "error.hpp"

class Shader 
{
public:

//create a shader
Shader(const char *vertexPath, const char *fragmentPath);
Shader(const char *vertexPath, const char *geometryPath, const char *fragmentPath);
Shader(const char *vertexPath, const char *tessellationPath,  const char *geometryPath, const char *fragmentPath);
~Shader();
// copy assignment
Shader(const Shader& s) = delete;
Shader operator=(const Shader& s) = delete;
//move assignment 
Shader(Shader&& s);
Shader operator=(Shader&& s);

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

int success;
std::ifstream vertFile;
std::ifstream geoFile;
std::ifstream fragFile;
// std::ifstream tessFile; //here for future creep scope?

private:

unsigned int ID;
void createShader();
const char *vPath = nullptr;
const char *gPath = nullptr;
const char *fPath = nullptr;
};

// for future maybe add opengl 4.3 to add compute shaders