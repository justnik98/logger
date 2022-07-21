//
// Created by justnik on 21.07.22.
//

#include <iostream>
#include "logger.hpp"
int Logger::cur_log_lvl = 3;
int main(){
    auto num  = 1000000;
    auto start = std::chrono::system_clock::now();
    for(auto i =0; i < num; ++i){
        LOG_DEBUG()<<"Hello world asdasd sdasd sad asd sad sad";
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to write " << std::setw(9)
              << num << " logs : " << diff.count() << " s\n";
    return 0;
}