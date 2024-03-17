#ifndef LOGGER_HH
#define LOGGER_HH

#include <iostream>

class Logger {

public:
    static void log(const char* msg);
    static void logerr(const char* msg);
};

#endif