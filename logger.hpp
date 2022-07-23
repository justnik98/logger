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
    static std::basic_string<char> log_file;
    static uint32_t max_file_size;
    std::ofstream os = std::ofstream(log_file, std::ios::app);
    Buffer oss;

    static auto timestamp() {
        auto now = time(nullptr);
        return now;
    }

public:

    static int get_log_lvl() { return cur_log_lvl; }

    static void set_log_lvl(int val) { cur_log_lvl = val; }

    static void set_log_file(std::string file) { log_file = std::move(file); }

    static void set_log_size(uint32_t val) { max_file_size = val; }

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
        ss << std::put_time(localtime(&now), "%F %T");
        oss << ss.str() << ' ';
    }

    ~Logger() {
        if (os.tellp() > max_file_size) {
            os.close();
            std::remove(log_file.c_str());
            os.open(log_file, std::ios::app);
        }
        os << oss;
        os << '\n';
    }

    template<typename T>
    inline Logger &operator<<(const T &value) {
        oss << value;
        return *this;
    }
};

inline int Logger::cur_log_lvl = DEBUG;
inline std::string Logger::log_file = "out";
inline uint32_t Logger::max_file_size = 2 << 30;


#endif //LOGGER_LOGGER_HPP
