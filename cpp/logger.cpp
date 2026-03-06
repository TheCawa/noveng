#include "logger.hpp"
#include "common.hpp"
#include <algorithm>

namespace fs = std::filesystem;

Logger::Logger() {
    fs::path logDir = fs::path(DIR_RES) / "log";
    if (!fs::exists(logDir)) fs::create_directories(logDir);

    std::string fileName = "engine_" + getTimestamp() + ".log";
    std::replace(fileName.begin(), fileName.end(), ':', '-');
    std::replace(fileName.begin(), fileName.end(), ' ', '_');
    
    logFile.open(logDir / fileName, std::ios::out | std::ios::app);
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& message, LogLevel level) {
    std::string formatted = "[" + getTimestamp() + "] [" + levelToString(level) + "] " + message;

    if (logFile.is_open()) {
        logFile << formatted << std::endl;
        logFile.flush();
    }

    if (level == LogLevel::Error) {
        std::cerr << "\x1B[1;31m" << formatted << "\x1B[0m" << std::endl;
    }
}

std::string Logger::getTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[20];
    struct tm* timeinfo = std::localtime(&now);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buf);
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Info:    return "INFO";
        case LogLevel::Warning: return "WARN";
        case LogLevel::Error:   return "ERROR";
        case LogLevel::Debug:   return "DEBUG";
        default:                return "UNKNOWN";
    }
}