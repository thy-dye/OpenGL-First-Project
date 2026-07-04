#include "shader.hpp"

// Constructors
Shader::Shader(const char *vertexPath, const char *fragmentPath) 
{
    vPath = vertexPath;
    fPath = fragmentPath;

    vertFile.open(vertexPath);
    fragFile.open(fragmentPath);

    if (vertFile.fail() || fragFile.fail()) {
        ID = NULL;
        if ( vertFile.fail() ) { err::log(LogLevel::CRIT, "SHADER::Error reading Vertex File."); }
        if ( fragFile.fail() ) { err::log(LogLevel::CRIT, "SHADER::Error reading Fragment File."); }
        return;
    }
    else {
        createShader();
    }
}
Shader::Shader(const char *vertexPath, const char *geometryPath, const char *fragmentPath)
{
    vPath = vertexPath;
    gPath = geometryPath;
    fPath = fragmentPath;

    vertFile.open(vertexPath);
    geoFile.open(geometryPath);
    fragFile.open(fragmentPath);

    if (vertFile.fail() || geoFile.fail() || fragFile.fail()) {
        ID = NULL;
        if ( vertFile.fail() ) { err::log(LogLevel::CRIT, "SHADER::Error reading Vertex File."); }
        if ( geoFile.fail() )  { err::log(LogLevel::CRIT, "SHADER::Error reading Geometry File."); }
        if ( fragFile.fail() ) { err::log(LogLevel::CRIT, "SHADER::Error reading Fragment File."); }
        return;
    }
    else {
        createShader();
    }
}
// Destructor
Shader::~Shader() { glDeleteProgram(ID); }
// Move constructor and assignment
Shader::Shader(Shader&& s) { *this = std::move(s); }
Shader Shader::operator=(Shader&& s)
{
    this->ID = s.ID;
    this->vPath = s.vPath;
    this->gPath = s.gPath;
    this->fPath = s.fPath;
    s.ID = 0;
    s.vPath = nullptr;
    s.gPath = nullptr;
    s.fPath = nullptr;
}

// Member Functions
void Shader::reloadShader(const char *vertexPath, const char *geometryPath, const char *fragmentPath) 
{
    if (vertexPath != nullptr)   { vPath = vertexPath; }
    if (geometryPath != nullptr) { gPath = geometryPath; }
    if (fragmentPath != nullptr) { fPath = fragmentPath; }
    
    vertFile.open(vPath);
    geoFile.open(gPath);
    fragFile.open(fPath);
    
    if (vertFile.fail() || geoFile.fail() || fragFile.fail()) {
        ID = NULL;
        if ( vertFile.fail() ) { err::log(LogLevel::CRIT, "SHADER::Error reading Vertex File."); }
        if ( geoFile.fail() )  { err::log(LogLevel::CRIT, "SHADER::Error reading Geometry File."); }
        if ( fragFile.fail() ) { err::log(LogLevel::CRIT, "SHADER::Error reading Fragment File."); }
        return;
    }
    else {
        createShader();
    }
}

// utility uniform functions
void Shader::setBool(const std::string &name, bool value) const                                 { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
void Shader::setInt(const std::string &name, int value) const                                   { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setFloat(const std::string &name, float value) const                               { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setVec4(const std::string &name, float v1, float v2, float v3, float v4) const     { glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4); }
void Shader::setVec3(const std::string &name, float v1, float v2, float v3) const               { glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3); }
void Shader::setVec2(const std::string &name, float v1, float v2) const                         { glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2); }

//private functions
void Shader::createShader()
{
    int  success;
    char infoLog[512];
    std::stringstream vertString, tessString, geoString, fragString;
    std::string vertCode, geoCode, tessCode, fragCode;

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    ID = glCreateProgram();
    
    if (vertFile.is_open()) {
        vertString << vertFile.rdbuf();
        vertCode = vertString.str();
        vertFile.close();    
        const char* vShaderCode = vertCode.c_str();

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
    
    // delete the shaders after linking successfully
    if (vertFile.is_open()) { glDeleteShader(vertexShader); }
    if (geoFile.is_open())  { glDeleteShader(geometryShader); }
    if (fragFile.is_open()) { glDeleteShader(fragmentShader); }
}