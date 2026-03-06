#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <ctime>

enum class LogLevel { 
    Info, 
    Warning, 
    Error,
    Debug 
};

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message, LogLevel level = LogLevel::Info);
    
    void info(const std::string& msg)  { log(msg, LogLevel::Info); }
    void warn(const std::string& msg)  { log(msg, LogLevel::Warning); }
    void error(const std::string& msg) { log(msg, LogLevel::Error); }
    void debug(const std::string& msg) { log(msg, LogLevel::Debug); }

private:
    Logger();
    ~Logger();
    std::ofstream logFile;
    std::string getTimestamp();
    std::string levelToString(LogLevel level);
};