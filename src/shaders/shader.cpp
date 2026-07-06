#include "shader.hpp"

// Constructors
Shader::Shader() {}
Shader::Shader(const char *vertexPath, const char *fragmentPath) 
{
    reloadShader(vertexPath, fragmentPath);
}
Shader::Shader(const char *vertexPath, const char *geometryPath, const char *fragmentPath)
{
    reloadShader(vertexPath, fragmentPath, geometryPath);
}
// Destructor
Shader::~Shader() { glDeleteProgram(ID); }
// Move constructor and assignment
Shader::Shader(Shader&& s) { *this = std::move(s); }
Shader& Shader::operator=(Shader&& s)
{
    this->ID = s.ID;
    this->vPath = s.vPath;
    this->gPath = s.gPath;
    this->fPath = s.fPath;
    s.ID = 0;
    s.vPath = nullptr;
    s.gPath = nullptr;
    s.fPath = nullptr;
    return *this; 
}

// Member Functions
void Shader::reloadShader(const char *vertexPath, const char *fragmentPath, const char *geometryPath) 
{
    if (vertexPath != nullptr)   { vPath = vertexPath; }
    if (geometryPath != nullptr) { gPath = geometryPath; }
    if (fragmentPath != nullptr) { fPath = fragmentPath; }

    if (vPath != nullptr) { loadShader(vPath, ShaderType::VERTEX_SHADER); }
    if (!success)         { err::log(LogLevel::CRIT, "SHADER::Error reading Vertex File."); }
    if (gPath != nullptr) { loadShader(gPath, ShaderType::GEOMETRY_SHADER); }
    if (!success)         { err::log(LogLevel::CRIT, "SHADER::Error reading Geometry File."); }
    if (fPath != nullptr) { loadShader(fPath, ShaderType::FRAGMENT_SHADER); }
    if (!success)         { err::log(LogLevel::CRIT, "SHADER::Error reading Fragment File."); }
        
    createShader();  
}

// utility functions to set uniforms in shaders 
void Shader::setBool(const std::string &name, bool value) const                                 { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
void Shader::setInt(const std::string &name, int value) const                                   { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setFloat(const std::string &name, float value) const                               { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setVec4(const std::string &name, float v1, float v2, float v3, float v4) const     { glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4); }
void Shader::setVec3(const std::string &name, float v1, float v2, float v3) const               { glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3); }
void Shader::setVec2(const std::string &name, float v1, float v2) const                         { glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2); }

//private helper functions
/**
 * Load a specific shader into the filepath
 *
 * Load a shader into its specific filepath and determine if 
 * it is a valid path or not
 *
 * @param shader - path to the file
 * @param shadertype - enum to designated shader type (see shader.hpp)
 * @return success = 0 on failure and success = 1 on success and an error message
 */
void Shader::loadShader(const char* shader, int shadertype)
{
    success = 0;
    if (shadertype == ShaderType::VERTEX_SHADER) 
    {
        vPath = shader;
        vertFile.open(vPath);
        if ( vertFile.fail() ) 
        { 
            err::log(LogLevel::CRIT, "SHADER::Error reading Vertex File.");
            return; 
        }
    }
    if (shadertype == ShaderType::GEOMETRY_SHADER) 
    {
        gPath = shader;
        geoFile.open(gPath);
        if ( geoFile.fail() )  
        { 
            err::log(LogLevel::CRIT, "SHADER::Error reading Geometry File.");
            return; 
        }
    }
    if (shadertype == ShaderType::FRAGMENT_SHADER) 
    {
        fPath = shader;
        fragFile.open(fPath);        
        if ( fragFile.fail() ) 
        { 
            err::log(LogLevel::CRIT, "SHADER::Error reading Fragment File."); 
            return;
        }
    }
    success = 1; //if the program made it here it was successful
}
/**
 * Compiles and links desginated shaders
 *
 * Compiles and links the designated shaders based on whether the filestream is open or not
 * and prints out an error message when occured during compile or linking time
 * @param None
 * @return success will be 0 on failure and 1 on success
 */
void Shader::createShader()
{
    char infoLog[512];
    std::stringstream vertString, geoString, fragString;
    std::string vertCode, geoCode, fragCode;
    unsigned int vertexShader, geometryShader, fragmentShader;
    
    ID = glCreateProgram();
    
    if (vertFile.is_open()) {
        vertString << vertFile.rdbuf();
        vertCode = vertString.str();
        vertFile.close();    
        const char* vShaderCode = vertCode.c_str();
        
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) // compilation errors
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::string log{infoLog};
            err::log(LogLevel::CRIT, "SHADER::VERT::ERROR" + log);
        }
        glAttachShader(ID, vertexShader);
    } 
    
    if (geoFile.is_open()) {
        geoString << geoFile.rdbuf();
        geoCode = geoString.str();
        geoFile.close();        
        const char* gShaderCode = geoCode.c_str();
        
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &gShaderCode, NULL);
        glCompileShader(geometryShader);
        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
        if (!success) // compilation errors
        {
            glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
            std::string log{infoLog};
            err::log(LogLevel::CRIT, "SHADER::GEO::ERROR" + log);
        }
        glAttachShader(ID, geometryShader);
    }
    
    if (fragFile.is_open()) {
        fragString << fragFile.rdbuf();
        fragCode = fragString.str();    
        fragFile.close();
        const char* fShaderCode = fragCode.c_str();
        
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) // compilation errors
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::string log{infoLog};
            err::log(LogLevel::CRIT, "SHADER::FRAG::ERROR" + log);
        }
        glAttachShader(ID, fragmentShader);
    }     
    
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    // linking errors
    if(!success) 
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::string log{infoLog};
        err::log(LogLevel::CRIT, "SHADER::LINKING::ERROR" + log);
    }
    
    // delete the shaders after linking successfully __ some optimization can be saved here so we dont have to recompile all the shaders on hot reload
    if (vertFile.is_open()) { glDeleteShader(vertexShader); }
    if (geoFile.is_open())  { glDeleteShader(geometryShader); }
    if (fragFile.is_open()) { glDeleteShader(fragmentShader); }
}