#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>

#define MAJOR 4
#define MINOR 0

#define WIDTH 800
#define HEIGHT 600

enum LogLevel { INFO, WARNING, CRIT };

namespace err 
{
const std::string& levelToString(LogLevel level) 
{
    if (level == LogLevel::INFO)          { return "INFO"; }
    else if (level == LogLevel::WARNING)  { return "WARNING"; }
    else if (level == LogLevel::CRIT)      { return "ERR"; }
    else { 
        std::string s{"UNKNOWN ERROR LEVEL"};
        return  s + std::to_string(level);
    }
}

void log(LogLevel level, const std::string& msg, const char *filename=nullptr) 
{
    if (filename) {
        std::ofstream logFile;
        logFile.open(filename, std::ios::out | std::ios::ate); 
        if (logFile.is_open()) { 
            logFile << "[" << levelToString(level) << '] ' << msg << std::endl; 
            logFile.close();
        }
        else {
            log(LogLevel::WARNING, "Unable to open file" + std::string{filename} + ". resorting to std::cout. ");
            log(level, msg);
        } 
    }
    else { std::cout << "[" << levelToString(level) << '] ' << msg << std::endl; }
}

}
