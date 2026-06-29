#pragma once
#include "all.hpp"

enum LogLevel { INFO, WARNING, CRIT };

namespace err 
{
    std::string levelToString(LogLevel level);
    void log(LogLevel level, const std::string& msg, const char *filename=nullptr);
}