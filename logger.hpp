//
// Created by justnik on 20.07.22.
//

#ifndef LOGGER_LOGGER_HPP
#define LOGGER_LOGGER_HPP

#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <fstream>
#include "buffer.hpp"

enum log_lvl {
    ERROR = 0, WARNING, INFO, DEBUG
};
#define LOG_DEBUG() \
    if(Logger::get_log_lvl() >= DEBUG) Logger(DEBUG)
#define LOG_INFO() \
    if(Logger::get_log_lvl() >= INFO)  Logger(INFO)
#define LOG_WARNING() \
    if(Logger::get_log_lvl() >= WARNING) Logger(WARNING)
#define LOG_ERROR() \
    if(Logger::get_log_lvl() >= ERROR) Logger(ERROR)

class Logger {
private:

    static int cur_log_lvl;
    std::ofstream os = std::ofstream("out", std::ios::app);
    //std::ostringstream oss;
    Buffer oss;

    static auto timestamp() {
        auto now = time(NULL);
        return now;
    }

public:

    static int get_log_lvl() { return cur_log_lvl; }
    static int set_log_lvl(int val) {  cur_log_lvl = val; }

    explicit Logger(int lvl) {
        switch (lvl) {
            case ERROR:
                oss << "[ERROR] ";
                break;
            case WARNING:
                oss << "[WARNING] ";
                break;
            case INFO:
                oss << "[INFO] ";
                break;
            case DEBUG:
                oss << "[DEBUG] ";
                break;
            default:
                oss << "";
        }
        auto now = timestamp();
        std::stringstream ss;
        ss <<std::put_time(localtime(&now), "%F %T");
        oss << ss.str() << ' ';
    }

    ~Logger() {
        os << oss;
        os << '\n';
    }

    template<typename T>
    inline Logger &operator<<(const T &value) {
        oss << value;
        return *this;
    }
};

#endif //LOGGER_LOGGER_HPP
