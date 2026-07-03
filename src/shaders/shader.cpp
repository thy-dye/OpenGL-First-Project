  #include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertCode;
    std::string fragCode;
    std::ifstream vertFile;
    std::ifstream fragFile;
    
    vertFile.open(vertexPath);
    fragFile.open(fragmentPath);
    if (vertFile.fail() | fragFile.fail()) {
        ID = NULL;
        if ( vertFile.fail() ) { err::log(LogLevel::CRIT, "SHADER::Error reading Vertex File."); }
        if ( fragFile.fail() ) { err::log(LogLevel::CRIT, "SHADER::Error reading Fragment File."); }
        return;
    }
    else {
        std::stringstream vertString, fragString;

        vertString << vertFile.rdbuf();
        fragString << fragFile.rdbuf();

        vertCode = vertString.str();
        fragCode = fragString.str();        
    }
    vertFile.close();
    fragFile.close();
    const char* vShaderCode = vertCode.c_str();
    const char* fShaderCode = fragCode.c_str();
    
    int  success;
    char infoLog[512];
    
    //creating vertex and fragment shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    //vertex first
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) // compilation errors
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::string log{infoLog};
        err::log(LogLevel::CRIT, "SHADER::VERT::ERROR" + log);
    }
    //fragment second
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) // compilation errors
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::string log{infoLog};
        err::log(LogLevel::CRIT, "SHADER::FRAG::ERROR" + log);
    }

    //linking the program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) // linking errors
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::string log{infoLog};
        err::log(LogLevel::CRIT, "SHADER::LINKING::ERROR" + log);
    }
    
    // delete the shaders after linking successfully
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(const char* vertexPath, const char* geometryPath, const char* fragmentPath)
{

}
Shader::Shader(const char* vertexPath, const char* tessellationPath,  const char* geometryPath, const char* fragmentPath)
{

}

//private helper function for initialization
void Shader::createShader()
{

}

// activate shader
void Shader::use() { glUseProgram(ID); }
void Shader::reloadShader() 
{

}

// utility uniform functions
void Shader::setBool(const std::string &name, bool value) const                                 { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
void Shader::setInt(const std::string &name, int value) const                                   { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setFloat(const std::string &name, float value) const                               { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setVec4(const std::string &name, float v1, float v2, float v3, float v4) const     { glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4); }
void Shader::setVec3(const std::string &name, float v1, float v2, float v3) const               { glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3); }
void Shader::setVec2(const std::string &name, float v1, float v2) const                         { glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2); }
