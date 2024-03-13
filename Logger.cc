#include "Logger.hh"
#include <iostream>

void Logger::log(const char* msg) {
    std::cout << "> " << msg << std::endl;
}