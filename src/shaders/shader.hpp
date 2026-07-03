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
Shader(const char* vertexPath, const char* fragmentPath);
Shader(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
Shader(const char* vertexPath, const char* tessellationPath,  const char* geometryPath, const char* fragmentPath);

//activate shader
void use();
void reloadShader();
//utility uniform functions
void setBool(const std::string &name, bool value) const;
void setInt(const std::string &name, int value) const;
void setFloat(const std::string &name, float value) const;
void setVec4(const std::string &name, float v1, float v2, float v3, float v4) const;
void setVec3(const std::string &name, float v1, float v2, float v3) const;
void setVec2(const std::string &name, float v1, float v2) const;

    int success;
    unsigned int ID;
    std::ifstream vertFile;
    std::ifstream geoFile;
    std::ifstream tessFile;
    std::ifstream fragFile;
private:
    void createShader();
};

//todo
// class ComputeShader
// {
// public:
//     ComputeShader(const char* computePath);
//     void use();
//     void reloadShader();
//     int success;

//     unsigned int ID;
//     std::ifstream computeFile;
// };