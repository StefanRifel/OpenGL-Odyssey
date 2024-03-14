#include "utils/Logger.hh"

void Logger::log(const char* msg) {
    std::cout << "> " << msg << std::endl;
}

void Logger::logerr(const char* error){
    std::cout << "> " << error << std::endl;
}