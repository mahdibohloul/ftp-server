//
// Created by mahdi on 24/03/2022.
//

#ifndef FTP_SERVER_LOGGER_HPP
#define FTP_SERVER_LOGGER_HPP

#include "string"
#include "../time/TimeService.hpp"
#include <fstream>
#include "iostream"

class Logger {
public:
    Logger(const std::string &name);

    Logger(const std::string &logFile, const std::string &name);

    void info(const char *message);

    void info(const std::string &message);

    void error(const char *message);

    void error(const std::string &message);

private:
    std::string log_file_name;
    std::string name;
};


#endif //FTP_SERVER_LOGGER_HPP
