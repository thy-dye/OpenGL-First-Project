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
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    //activate shader
    void use();
    void addGeometryShader();
    void addComputeShader();
    //utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec4(const std::string &name, float value) const;
    void setVec3(const std::string &name, float value) const;
    void setVec2(const std::string &name, float value) const;

};
